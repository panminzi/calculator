#include <QGridLayout>
#include <QFont>
#include <QPushButton>
#include <QMessageBox>
#include <QStack>
#include <QMouseEvent>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTextEdit>
#include"calculator.h"
Calculator::Calculator(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
    setupModules();
    createButtons();
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

    // 按钮网格布局
    m_pButtonLayout = new QGridLayout;
    m_pButtonLayout->setSpacing(3);
    mainLayout->addLayout(m_pButtonLayout, 7);

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

    // 设置按钮拉伸比例
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
    connect(m_pSideBar, &Sidebar::closed, [this] { /* 可添加关闭后操作 */ });
    // 连接新模式信号
     //   connect(m_pSideBar, &Sidebar::itemClicked,
     //       this, &Calculator::handleModeChange);
}

// 核心计算逻辑 -------------------------------------------------
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
    if (m_pScientificPanel) {
        m_pScientificPanel->setFixedHeight(height() * 0.3);
    }
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
    QList<QPushButton*> buttons = findChildren<QPushButton*>();
    foreach(QPushButton * btn, buttons) {
        if (btn != m_pTopBar->historyButton())
            btn->setFont(btnFont);
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
void Calculator::handleModeChange(const QString& mode)
{
    clearCurrentUI();

    if (mode == u8"标准") {
        setupStandardUI();
    }
    else if (mode == u8"科学") {
        setupScientificUI();
    }

    update();  // 触发界面更新
}
void Calculator::setupStandardUI()
{
    // 标准模式界面（保持原有布局）
    createButtons();  // 重建标准按钮
}

void Calculator::setupScientificUI()
{
    // 科学模式界面（示例实现）
    m_pScientificPanel = new QWidget;
    QGridLayout* sciLayout = new QGridLayout(m_pScientificPanel);

    // 添加科学计算按钮（示例）
    const QString sciButtons[4][5] = {
        {"sin", "cos", "tan", "(", ")"},
        {"log", "ln", "π", "^", "√"},
        {"x²", "x³", "e", "!", "±"},
        {"(", ")", "Rad", "Deg", ""}
    };

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (sciButtons[row][col].isEmpty()) continue;

            QPushButton* btn = new QPushButton(sciButtons[row][col]);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            sciLayout->addWidget(btn, row, col);
        }
    }

    // 将科学面板添加到主布局
    dynamic_cast<QVBoxLayout*>(layout())->insertWidget(2, m_pScientificPanel);
}

void Calculator::clearCurrentUI()
{
    // 移除科学面板
    if (m_pScientificPanel) {
        layout()->removeWidget(m_pScientificPanel);
        delete m_pScientificPanel;
        m_pScientificPanel = nullptr;
    }

    // 清除原有按钮
    QLayoutItem* item;
    while (item = m_pButtonLayout->takeAt(0))
    {
        delete item->widget();
        delete item;
    }
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