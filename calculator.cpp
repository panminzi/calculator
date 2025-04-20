#include "calculator.h"
#include <QGridLayout>
#include <QFont>
#include <QPushButton>
#include <QMessageBox>
#include <QStack>
#include <QMouseEvent>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTextEdit>

Calculator::Calculator(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
    createButtons();
    connectSignals();
}

void Calculator::setupUI()
{
    // ������
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(5);

    // ����������
    m_topBar = new TopBar(this);
    mainLayout->addWidget(m_topBar);

    // ��ʾ����
    m_pDisplay = new QTextEdit;
    m_pDisplay->setReadOnly(true);
    m_pDisplay->setAlignment(Qt::AlignRight);
    mainLayout->addWidget(m_pDisplay, 2);

    // ��ť���񲼾�
    m_pButtonLayout = new QGridLayout;
    m_pButtonLayout->setSpacing(3);
    mainLayout->addLayout(m_pButtonLayout, 7);

    // �ɲ�����
    m_overlay = new QWidget(this);
    m_overlay->setStyleSheet("background: rgba(0,0,0,0.3);");
    m_overlay->hide();
    m_overlay->installEventFilter(this);
    m_overlay->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    // ��ʷ����
    m_historyPopup = new HistoryPopup(this);
    m_overlay->stackUnder(m_historyPopup);
}

void Calculator::createButtons()
{
    const QString buttons[4][5] = {
        {"7", "8", "9", "/", "C"},
        {"4", "5", "6", "*", "B"},
        {"1", "2", "3", "-", ""},
        {"0", ".", "=", "+", ""}
    };

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (buttons[row][col].isEmpty()) continue;

            const QString& text = buttons[row][col];
            QPushButton* btn = nullptr;

            if (text == "C") {
                btn = createButton(text, SLOT(clearExpression()));
            }
            else if (text == "=") {
                btn = createButton(text, SLOT(equalClicked()));
            }
            else if (text == "B") {
                btn = createButton(text, SLOT(backspaceClicked()));
            }
            else if (text.at(0).isDigit() || text == ".") {
                btn = createButton(text, SLOT(digitClicked()));
            }
            else {
                btn = createButton(text, SLOT(operatorClicked()));
            }

            m_pButtonLayout->addWidget(btn, row, col);
        }
    }

    // ���ð�ť�������
    for (int i = 0; i < 4; ++i)
        m_pButtonLayout->setRowStretch(i, 1);
    for (int i = 0; i < 5; ++i)
        m_pButtonLayout->setColumnStretch(i, 1);
}

QPushButton* Calculator::createButton(const QString& text, const char* member)
{
    QPushButton* btn = new QPushButton(text);
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(btn, SIGNAL(clicked()), this, member);
    return btn;
}

void Calculator::connectSignals()
{
    // �����������ź�
    connect(m_topBar, &TopBar::historyClicked, this, &Calculator::toggleHistoryWindow);

    // ��ʷ�����ź�
    connect(m_historyPopup, &HistoryPopup::closed, [this] { m_overlay->hide(); });
    connect(m_historyPopup, &HistoryPopup::clearRequested, &m_historyManager, &HistoryManager::clear);

    // ��ʷ�����ź�
    connect(&m_historyManager, &HistoryManager::historyChanged, this, [this] {
        m_historyPopup->updateHistory(m_historyManager.history());
        });
}

// ���ļ����߼� -------------------------------------------------
void Calculator::digitClicked()
{
    if (m_hasCalcError) resetAfterError();

    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    m_expression += btn->text();
    updateDisplay();
}

void Calculator::operatorClicked()
{
    if (m_hasCalcError) resetAfterError();

    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QString op = btn->text();

    if (!m_expression.isEmpty() && isOperator(m_expression[m_expression.length() - 1]))
        m_expression.chop(1);

    m_expression += op;
    updateDisplay();
}
/*
void Calculator::equalClicked()
{
    m_hasCalcError = false;
    m_lastValidExpression = m_expression;

    try {
        double result = evaluateExpression(m_expression);
        showResult(result);
        m_historyManager.addEntry(m_lastValidExpression + " = " + QString::number(result));
    }
    catch (const std::exception& e) {
        handleCalculationError(e.what());
    }
}
*/
void Calculator::equalClicked()
{
    m_hasCalcError = false;
    m_lastValidExpression = m_expression;
    double result = evaluateExpression(m_expression);
    if (m_hasCalcError)
    {
        QMessageBox::warning(this, u8"����", m_calcErrorMsg, QMessageBox::Ok);
        m_pDisplay->setStyleSheet("QTextEdit { color: red; }");
        m_expression = m_lastValidExpression; // �ָ�ԭʼ���ʽ
        m_pDisplay->setText(m_expression);
        return;
    }
    showResult(result);
    // ��¼��ʷ�����ı���
    m_historyManager.addEntry(m_lastValidExpression + " = " + QString::number(result));
    
}

void Calculator::backspaceClicked()
{
    if (!m_expression.isEmpty()) {
        m_expression.chop(1);
        updateDisplay();
    }
}

void Calculator::clearExpression()
{
    m_expression.clear();
    m_pDisplay->setStyleSheet("");
    m_pDisplay->setText("0");
}

// �������� -----------------------------------------------------
void Calculator::resetAfterError()
{
    m_hasCalcError = false;
    m_pDisplay->setStyleSheet("");
    m_expression.clear();
}

void Calculator::updateDisplay()
{
    m_pDisplay->setPlainText(m_expression.isEmpty() ? "0" : m_expression);
}

void Calculator::showResult(double result)
{
    m_pDisplay->clear();
    QTextCursor cursor(m_pDisplay->document());

    // ԭ���ʽ����ɫ��
    QTextCharFormat grayFormat;
    grayFormat.setForeground(QColor(151, 151, 151));
    cursor.insertText(m_lastValidExpression + " =", grayFormat);

    // �������ɫ��
    cursor.insertBlock();//����
    cursor.insertText(QString::number(result));

    m_expression = QString::number(result);
}

void Calculator::handleCalculationError(const QString& msg)
{
    m_hasCalcError = true;
    QMessageBox::warning(this, u8"����", msg, QMessageBox::Ok);
    m_pDisplay->setStyleSheet("color: red;");
    m_expression = m_lastValidExpression;
    updateDisplay();
}

// ���ʽ��ֵ�߼� -----------------------------------------------
double Calculator::evaluateExpression(QString expr) {
    QStack<double> numbers;
    QStack<QChar> ops;
    QString numBuffer;
    auto processNumBuffer = [&]()
    {
        if (!numBuffer.isEmpty())
        {
            numbers.push(numBuffer.toDouble());
            numBuffer.clear();
        }
    };
    for (int i = 0; i < expr.length(); ++i)
    {
        QChar c = expr[i];
        if (c.isDigit() || c == '.')
        {
            numBuffer += c;
        }
        else if (isOperator(c) && i == expr.length() - 1)
        {
            m_hasCalcError = true;
            m_calcErrorMsg = u8"ȱ�ٲ�����";
        }
        else if (isOperator(c))
        {
            processNumBuffer();
            while (!ops.isEmpty() && hasPriority(c, ops.top()))
            {
                calculateStep(numbers, ops);
            }
            ops.push(c);
        }
    }
    processNumBuffer();
    while (!ops.isEmpty())
        calculateStep(numbers, ops);
    return numbers.isEmpty() ? 0 : numbers.pop();
}

void Calculator::calculateStep(QStack<double>& nums, QStack<QChar>& ops)
{
    if (nums.size() < 2 || ops.isEmpty()) return;//ֱ�ӷ���ԭ����
    double b = nums.pop();
    double a = nums.pop();
    QChar op = ops.pop();
    switch (op.toLatin1()) {
    case '+': nums.push(a + b); break;
    case '-': nums.push(a - b); break;
    case '*': nums.push(a * b); break;
    case '/':
        if (b == 0) {
            m_hasCalcError = true; // ���ô���״̬
            m_calcErrorMsg = u8"��������Ϊ0";
            nums.clear();
            ops.clear();
            return;
        }
        nums.push(a / b);
        break;
    }
}

// ������ط��� -------------------------------------------------
void Calculator::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    // �����ɲ�ߴ�
    m_overlay->setGeometry(rect());

    // ��̬��������
    const int baseSize = qMin(width(), height()) / 20;
    const int mainFontSize = qMax(20, static_cast<int>(height() * 0.08));

    // ��ʾ������
    QFont displayFont = m_pDisplay->font();
    displayFont.setPixelSize(mainFontSize);
    m_pDisplay->setFont(displayFont);

    // ��ʷ��������
    m_historyPopup->updateFontSize(mainFontSize * 0.7);

    // ��ť����
    QFont btnFont = font();
    btnFont.setPixelSize(qMax(12, baseSize));
    QList<QPushButton*> buttons = findChildren<QPushButton*>();
    foreach(QPushButton * btn, buttons) {
        if (btn != m_topBar->historyButton())
            btn->setFont(btnFont);
    }

    // ������ʷ��ť
    const int btnSize = qMax(24, baseSize * 2);
    m_topBar->updateButtonSize(btnSize);

    // ���µ���λ��
    updatePopupLayout();
}

void Calculator::updatePopupLayout()
{
    QRect rect = geometry();
    rect.setTop(rect.bottom() - height() / 2);
    m_historyPopup->setGeometry(rect);
}

bool Calculator::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == m_overlay && event->type() == QEvent::MouseButtonRelease) {
        m_historyPopup->hidePopup();
        m_overlay->hide();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void Calculator::toggleHistoryWindow()
{
    m_historyPopup->updateHistory(m_historyManager.history());
    updatePopupLayout();
    m_overlay->raise();
    m_overlay->show();
    m_historyPopup->raise();
    m_historyPopup->showPopup();
}

// ������жϸ������� --------------------------------------------
bool Calculator::isOperator(QChar c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool Calculator::hasPriority(QChar op1, QChar op2)
{
    return ((op2 == '*' || op2 == '/') && (op1 == '+' || op1 == '-'));
}