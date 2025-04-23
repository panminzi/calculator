#include <QFont>
#include <QPushButton>
#include <QMessageBox>
#include <QStack>
#include <QMouseEvent>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTextEdit>
#include<QVBoxLayout>
#include<QDebug>
#include"scientificpad.h"
#include"calculator.h"
#include"standardpad.h"
#include"scientificpad.h"
#include<QStackedWidget>
// 构造函数
Calculator::Calculator(QWidget * parent)
    : QWidget(parent), m_currentMode(u8"标准") {
    setupUI();
    setupModules();
    setMinimumSize(400, 500);

    // 初始化堆叠容器并添加键盘
    m_keyboardStack = new QStackedWidget(this);
    m_standardPad = new StandardPad();
    m_scientificPad = new ScientificPad();
    m_keyboardStack->addWidget(m_standardPad);
    m_keyboardStack->addWidget(m_scientificPad);
    m_keyboardStack->setCurrentWidget(m_standardPad); // 默认显示标准键盘
    m_currentPad = m_standardPad;
    setupKeyboardLayout();
    // 将堆叠容器添加到主布局
    QVBoxLayout* mainLayout = qobject_cast<QVBoxLayout*>(layout());
    mainLayout->insertWidget(2, m_keyboardStack, 7); // 调整位置权重

    connectSignals();
}

void Calculator::setupUI()
{
    // 主布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(5);

    m_pSideBar = new Sidebar(this);
    m_pSideBar->move(-m_pSideBar->width(), 0);
    // 顶部工具栏
    m_pTopBar = new TopBar(m_pSideBar, this);
    mainLayout->addWidget(m_pTopBar, 1);

    // 显示区域
    m_pDisplay = new QTextEdit;
    m_pDisplay->setReadOnly(true);
    m_pDisplay->setAlignment(Qt::AlignRight);
    mainLayout->addWidget(m_pDisplay, 2);

    // 蒙层设置
    m_overlay = new QWidget(this);
    m_overlay->setStyleSheet("background: rgba(0,0,0,0.3);");
    m_overlay->hide();
    m_overlay->installEventFilter(this);
    m_overlay->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    // 历史弹窗
    m_historyPopup = new HistoryPopup(this);
    m_overlay->stackUnder(m_historyPopup);
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
    // 顶部工具栏信号
    connect(m_pTopBar, &TopBar::historyClicked, this, &Calculator::toggleHistoryWindow);
    connect(m_pTopBar, &TopBar::showModeMenu, this, &Calculator::toggleSideBar);

    // 历史弹窗信号
    connect(m_historyPopup, &HistoryPopup::closed, [this] { m_overlay->hide(); });
    connect(m_historyPopup, &HistoryPopup::clearRequested, &m_historyManager, &HistoryManager::clear);

    // 历史管理信号
    connect(&m_historyManager, &HistoryManager::historyChanged, this, [this] {
        m_historyPopup->updateHistory(m_historyManager.history());
        });

    connect(m_pSideBar, &Sidebar::itemClicked, this, &Calculator::handleModeChange);
    connect(m_pSideBar, &Sidebar::closed, [this] {});

}

// 核心计算逻辑 -------------------------------------------------
void Calculator::digitClicked(QString digit) {
    qDebug() << "Received digit:" << digit;
    if (m_hasCalcError) resetAfterError();
    m_expression += digit;
    updateDisplay();
}

void Calculator::operatorClicked(QString op) {
    qDebug() << "Received operator:" << op;
    if (m_hasCalcError) resetAfterError();

    // 替换末尾的运算符
    if (!m_expression.isEmpty() && isOperator(m_expression[m_expression.length()-1])) {
        m_expression.chop(1);
    }
    m_expression += op;
    updateDisplay();
}

void Calculator::equalClicked()
{
    m_hasCalcError = false;
    m_lastValidExpression = m_expression;
    double result = evaluateExpression(m_expression);
    if (m_hasCalcError)
    {
        QMessageBox::warning(this, u8"错误", m_calcErrorMsg, QMessageBox::Ok);
        m_pDisplay->setStyleSheet("QTextEdit { color: red; }");
        m_expression = m_lastValidExpression; // 恢复原始表达式
        m_pDisplay->setText(m_expression);
        return;
    }
    showResult(result);
    // 记录历史（纯文本）
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

// 辅助方法 -----------------------------------------------------
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

    // 原表达式（灰色）
    QTextCharFormat grayFormat;
    grayFormat.setForeground(QColor(151, 151, 151));
    cursor.insertText(m_lastValidExpression + " =", grayFormat);

    // 结果（黑色）
    cursor.insertBlock();//换行
    cursor.insertText(QString::number(result));

    m_expression = QString::number(result);
}

void Calculator::handleCalculationError(const QString& msg)
{
    m_hasCalcError = true;
    QMessageBox::warning(this, u8"错误", msg, QMessageBox::Ok);
    m_pDisplay->setStyleSheet("color: red;");
    m_expression = m_lastValidExpression;
    updateDisplay();
}

// 表达式求值逻辑 -----------------------------------------------
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
            m_calcErrorMsg = u8"缺少操作数";
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
    if (nums.size() < 2 || ops.isEmpty()) return;//直接返回原数据
    double b = nums.pop();
    double a = nums.pop();
    QChar op = ops.pop();
    switch (op.toLatin1()) {
    case '+': nums.push(a + b); break;
    case '-': nums.push(a - b); break;
    case '*': nums.push(a * b); break;
    case '/':
        if (b == 0) {
            m_hasCalcError = true; // 设置错误状态
            m_calcErrorMsg = u8"除数不能为0";
            nums.clear();
            ops.clear();
            return;
        }
        nums.push(a / b);
        break;
    }
}
void Calculator::updatePopupLayout()
{
    QRect rect = geometry();
    rect.setTop(rect.bottom() - height() / 2);
    m_historyPopup->setGeometry(rect);
}
// 界面相关方法 -------------------------------------------------
void Calculator::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    // 动态调整时考虑科学模式面板
   // if (m_pScientificPanel) {
    //    m_pScientificPanel->setFixedHeight(height() * 0.3);
   // }
    // 更新蒙层尺寸
    m_overlay->setGeometry(rect());

    // 动态调整字体
    const int baseSize = qMin(width(), height()) / 20;
    const int mainFontSize = qMax(20, static_cast<int>(height() * 0.08));

    // 显示框字体
    QFont displayFont = m_pDisplay->font();
    displayFont.setPixelSize(mainFontSize);
    m_pDisplay->setFont(displayFont);

    // 历史弹窗字体
    m_historyPopup->updateFontSize(mainFontSize * 0.7);

    // 按钮字体
    QFont btnFont = font();
    btnFont.setPixelSize(qMax(12, baseSize));
    QList<NumberPad*> pads = findChildren<NumberPad*>();
    foreach(NumberPad * pad, pads) {
        QList<QPushButton*> btns = pad->findChildren<QPushButton*>();
        foreach(QPushButton * b, btns) {
            b->setFont(btnFont);
        }
    }


    const int btnSize = qMax(24, baseSize * 2);
    m_pTopBar->updateButtonSize(btnSize);

    // 更新弹窗位置
    updatePopupLayout();

    // 同步更新侧边栏尺寸
    if (m_pSideBar) {
        const int sidebarWidth = width() * 0.3;
        m_pSideBar->setFixedSize(sidebarWidth, height());
        m_pSideBar->move(m_pSideBar->isVisible() ? 0 : -sidebarWidth, 0);
    }
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
void Calculator::toggleSideBar()
{
    m_pSideBar->updateGeometry();
    m_pSideBar->updatePosition();
    m_pSideBar->raise();
    m_pSideBar->show();
    m_historyPopup->updateHistory(m_historyManager.history());
}

// 运算符判断辅助方法 --------------------------------------------
bool Calculator::isOperator(QChar c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool Calculator::hasPriority(QChar op1, QChar op2)
{
    return ((op2 == '*' || op2 == '/') && (op1 == '+' || op1 == '-'));
}

// 添加模式处理实现
void Calculator::handleModeChange(const QString& mode) {

    QSize currentSize = size(); // 保存当前窗口尺寸
    m_currentMode = mode;
    setupKeyboardLayout();
    resize(currentSize); // 强制恢复原窗口尺寸
}

void Calculator::setupModules()
{

    // 先创建侧边栏
   // m_pSideBar = new Sidebar(this);
    m_pSideBar->addMenuItem(u8"标准", QIcon(":/calculator/images/icon_standard.png"));
    m_pSideBar->addMenuItem(u8"科学", QIcon(":/calculator/images/icon_scientific.png"));

    // 连接信号
    connect(m_pSideBar, &Sidebar::itemClicked,
        this, &Calculator::handleModeChange);
}

void Calculator::setupKeyboardLayout() {
    if (m_currentPad) {
        //一定要断开，不然就会触发多个信号。
        disconnect(m_currentPad, &NumberPad::digitClicked, this, &Calculator::digitClicked);
        disconnect(m_currentPad, &NumberPad::operatorClicked, this, &Calculator::operatorClicked);
        disconnect(m_currentPad, &NumberPad::equalClicked, this, &Calculator::equalClicked);
        disconnect(m_currentPad, &NumberPad::controlClicked, this, nullptr);
   }
    // 根据模式切换显示的键盘
    if (m_currentMode == u8"标准") {
        m_currentPad = m_standardPad;
        m_keyboardStack->setCurrentWidget(m_standardPad);
    }
    else {
        m_currentPad = m_scientificPad;
        m_keyboardStack->setCurrentWidget(m_scientificPad);
    }
    // 显示新键盘并连接所有信号
    connect(m_currentPad, &NumberPad::digitClicked, this, &Calculator::digitClicked);
    connect(m_currentPad, &NumberPad::operatorClicked, this, &Calculator::operatorClicked);
    connect(m_currentPad, &NumberPad::equalClicked, this, &Calculator::equalClicked);
    connect(m_currentPad, &NumberPad::controlClicked, this, [this](QString cmd) {
        if (cmd == "C") clearExpression();
        else if (cmd == "B") backspaceClicked();
        });

    // 强制刷新布局
    m_keyboardStack->currentWidget()->layout()->activate();
    update();
}