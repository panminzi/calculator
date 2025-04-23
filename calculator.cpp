#include <QFont>
#include <QPushButton>
#include <QMessageBox>
#include <QStack>
#include <QMouseEvent>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QDebug>
#include <QStackedWidget>

#include "scientificpad.h"
#include "calculator.h"
#include "standardpad.h"
#include "scientificpad.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , m_currentMode("standard") 
{
    setupUI();
    setupModules();
    setMinimumSize(400, 500);

    // 初始化堆叠容器并添加键盘
    m_pKeyboardStack = new QStackedWidget(this);
    m_pStandardPad = new StandardPad();
    m_pScientificPad = new ScientificPad();
    m_pKeyboardStack->addWidget(m_pStandardPad);
    m_pKeyboardStack->addWidget(m_pScientificPad);
    m_pKeyboardStack->setCurrentWidget(m_pStandardPad); // 默认显示标准键盘
    m_pCurrentPad = m_pStandardPad;
    setupKeyboardLayout();
    // 将堆叠容器添加到主布局
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(layout());
    mainLayout->insertWidget(2, m_pKeyboardStack, 7);
    connectSignals();
}

void Calculator::setupUI()
{
    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(5);

    m_pSideBar = new Sidebar(this);
    m_pSideBar->move(-m_pSideBar->width(), 0);
    // 顶部工具栏
    m_pTopBar = new TopBar(m_pSideBar, this);
    mainLayout->addWidget(m_pTopBar, 1);

    // 显示区域
    m_pDisplay = new QTextEdit;
    QPalette palette = m_pDisplay->palette();
    palette.setColor(QPalette::Text, Qt::black);
    m_pDisplay->setPalette(palette);
    m_pDisplay->setReadOnly(true);
    m_pDisplay->setAlignment(Qt::AlignRight);
    mainLayout->addWidget(m_pDisplay, 2);

    // 蒙层设置
    m_pOverlay = new QWidget(this);
    m_pOverlay->setStyleSheet("background: rgba(0,0,0,0.3);");
    m_pOverlay->hide();
    m_pOverlay->installEventFilter(this);
    m_pOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    // 历史弹窗
    m_pHistoryPopup = new HistoryPopup(this);
    m_pOverlay->stackUnder(m_pHistoryPopup);
}

void Calculator::connectSignals()
{
    // 顶部工具栏信号
    connect(m_pTopBar, &TopBar::historyClicked, this, &Calculator::toggleHistoryWindow);
    connect(m_pTopBar, &TopBar::showModeMenu, this, &Calculator::toggleSideBar);
    // 历史弹窗信号
    connect(m_pHistoryPopup, &HistoryPopup::closed, [this] { m_pOverlay->hide(); });
    connect(m_pHistoryPopup, &HistoryPopup::clearRequested, &m_historyManager, &HistoryManager::clear);
    // 历史管理信号
    connect(&m_historyManager, &HistoryManager::historyChanged, this, [this] {
        m_pHistoryPopup->updateHistory(m_historyManager.history());
        });
    connect(m_pSideBar, &Sidebar::itemClicked, this, &Calculator::handleModeChange);
    connect(m_pSideBar, &Sidebar::closed, [this] {});
    connect(m_pSideBar, &Sidebar::itemClicked,this, &Calculator::handleModeChange);
}

void Calculator::digitClicked(QString digit) 
{
    if (m_hasCalcError) resetAfterError();
    m_expression += digit;
    updateDisplay();
}

void Calculator::operatorClicked(QString op)
{
    if (m_hasCalcError)
        resetAfterError();
    if (op == "(") 
    {
        // 允许运算符后直接跟左括号
        if (!m_expression.isEmpty() && isOperator(m_expression[m_expression.length() - 1])) 
            m_expression += op;
        else 
            m_expression += op;
    }
    else if (op == ")") 
    {
        m_expression += op;
    }
    else 
    {
        // 普通运算符：替换最后一个运算符
        if (!m_expression.isEmpty() && isOperator(m_expression[m_expression.length() - 1])) 
            m_expression.chop(1);
        m_expression += op;
    }
    updateDisplay();
}

void Calculator::equalClicked()
{
    m_hasCalcError = false;
    m_lastValidExpression = m_expression;
    double result = evaluateExpression(m_expression);
    if (m_hasCalcError)
    {
        QMessageBox::warning(this, "error", m_calcErrorMsg, QMessageBox::Ok);
        m_pDisplay->setStyleSheet("QTextEdit { color: red; }");
        m_expression = m_lastValidExpression; // 恢复原始表达式
        m_pDisplay->setText(m_expression);
        return;
    }
    showResult(result);
    // 记录历史
    m_historyManager.addEntry(m_lastValidExpression + " = " + QString::number(result));
}

void Calculator::backspaceClicked()
{
    if (!m_expression.isEmpty()) 
    {
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

void Calculator::resetAfterError()
{
    m_hasCalcError = false;
    m_pDisplay->clear();
    // 重置为黑色字体
    QPalette defaultPalette = m_pDisplay->palette();
    defaultPalette.setColor(QPalette::Text, Qt::black);
    m_pDisplay->setPalette(defaultPalette);
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
    QTextCharFormat resultFormat;
    resultFormat.setFont(m_pDisplay->font()); // 继承显示框当前字体
    cursor.insertText(QString::number(result), resultFormat);
    m_expression = QString::number(result);
}

void Calculator::handleCalculationError(const QString &msg)
{
    m_hasCalcError = true;
    QMessageBox::warning(this, "error", msg, QMessageBox::Ok);
    m_pDisplay->setStyleSheet("color: red;");
    m_expression = m_lastValidExpression;
    updateDisplay();
}

// 表达式求值
double Calculator::evaluateExpression(QString expr)
{
    // 预处理：处理负号（如 "-5" → "0-5"）
    expr.replace(QRegularExpression("(?<=^|\\()\\-"), "0-");
    // 检查括号匹配
    int bracketCount = 0;
    for (QChar c : expr) 
    {
        if (c == '(') 
            bracketCount++;
        else if (c == ')') 
            bracketCount--;
        if (bracketCount < 0) 
        {
            m_hasCalcError = true;
            m_calcErrorMsg = "parentheses not match";
            return 0;
        }
    }
    if (bracketCount != 0) 
    {
        m_hasCalcError = true;
        m_calcErrorMsg = "parentheses not match";
        return 0;
    }
    // 检查表达式末尾非法运算符
    if (!expr.isEmpty() && isOperator(expr[expr.length()-1]) && expr[expr.length() - 1] != ')') {
        m_hasCalcError = true;
        m_calcErrorMsg = "expression is incomplete";
        return 0;
    }

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
        if (c.isDigit() || c == '.' || (c == '-' && (i == 0 || isOperator(expr[i - 1])))) 
        {
            numBuffer += c;
        }
        else if (isOperator(c))
        {
            processNumBuffer();
            if (c == '(') 
            {
                ops.push(c);
            }
            else if (c == ')') 
            {
                while (!ops.isEmpty() && ops.top() != '(')
                {
                    calculateStep(numbers, ops);
                }
                if (!ops.isEmpty())
                {
                    ops.pop(); // 弹出左括号
                }
                else 
                {
                    m_hasCalcError = true;
                    m_calcErrorMsg = "parentheses not match";
                    return 0;
                }
            }
            else 
            {
                while (!ops.isEmpty() && hasPriority(c, ops.top()))
                {
                    calculateStep(numbers, ops);
                }
                ops.push(c);
            }
        }
    }
    processNumBuffer();
    while (!ops.isEmpty())
        calculateStep(numbers, ops);
    return numbers.isEmpty() ? 0 : numbers.pop();
}
void Calculator::calculateStep(QStack<double> &nums, QStack<QChar> &ops)
{
    if (nums.size() < 2 || ops.isEmpty())
        return;//直接返回原数据
    double b = nums.pop();
    double a = nums.pop();
    QChar op = ops.pop();
    switch (op.toLatin1()) 
    {
    case '+': nums.push(a + b); break;
    case '-': nums.push(a - b); break;
    case '*': nums.push(a * b); break;
    case '/':
        if (b == 0) {
            m_hasCalcError = true; // 设置错误状态
            m_calcErrorMsg = "divisor cannot be zero";
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
    m_pHistoryPopup->setGeometry(rect);
}

void Calculator::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    // 更新蒙层尺寸
    m_pOverlay->setGeometry(rect());
    // 动态调整字体
    const int baseSize = qMin(width(), height()) / 20;
    const int mainFontSize = qMax(20, static_cast<int>(height() * 0.08));
    // 显示框字体
    QFont displayFont = m_pDisplay->font();
    displayFont.setPixelSize(mainFontSize);
    m_pDisplay->setFont(displayFont);
    // 历史弹窗字体
    m_pHistoryPopup->updateFontSize(mainFontSize * 0.7);
    // 按钮字体
    QFont btnFont = font();
    btnFont.setPixelSize(qMax(12, baseSize));
    QList<BasicPad*> pads = findChildren<BasicPad*>();
    foreach(BasicPad * pad, pads) 
    {
        QList<QPushButton*> btns = pad->findChildren<QPushButton*>();
        foreach(QPushButton * b, btns) 
        {
            b->setFont(btnFont);
        }
    }
    const int btnSize = qMax(24, baseSize * 2);
    m_pTopBar->updateButtonSize(btnSize);
    // 更新弹窗位置
    updatePopupLayout();
    // 同步更新侧边栏尺寸
    if (m_pSideBar)
    {
        const int sidebarWidth = width() * 0.3;
        m_pSideBar->setFixedSize(sidebarWidth, height());
        m_pSideBar->move(m_pSideBar->isVisible() ? 0 : -sidebarWidth, 0);
    }
}

bool Calculator::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_pOverlay && event->type() == QEvent::MouseButtonRelease) 
    {
        m_pHistoryPopup->hidePopup();
        m_pOverlay->hide();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void Calculator::toggleHistoryWindow()
{
    m_pHistoryPopup->updateHistory(m_historyManager.history());
    updatePopupLayout();
    m_pOverlay->raise();
    m_pOverlay->show();
    m_pHistoryPopup->raise();
    m_pHistoryPopup->showPopup();
}

void Calculator::toggleSideBar()
{
    m_pSideBar->updateGeometry();
    m_pSideBar->updatePosition();
    m_pSideBar->raise();
    m_pSideBar->show();
    m_pHistoryPopup->updateHistory(m_historyManager.history());
}

bool Calculator::isOperator(QChar c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

bool Calculator::hasPriority(QChar op1, QChar op2) 
{
    if (op2 == '(' || op2 == ')') 
        return false;  
    if (op1 == '(') 
        return false;                
    return ((op2 == '*' || op2 == '/') && (op1 == '+' || op1 == '-'));
}

void Calculator::handleModeChange(const QString &mode) 
{
    QSize currentSize = size(); // 保存当前窗口尺寸
    m_currentMode = mode;
    setupKeyboardLayout();
    resize(currentSize); // 强制恢复原窗口尺寸
}

void Calculator::setupModules()
{
    m_pSideBar->addMenuItem(u8"standard", QIcon(":/calculator/images/icon_standard.png"));
    m_pSideBar->addMenuItem(u8"science", QIcon(":/calculator/images/icon_scientific.png"));
}

void Calculator::setupKeyboardLayout()
{
    if (m_pCurrentPad)
    {
        //一定要断开，不然就会触发多个信号。
        disconnect(m_pCurrentPad, &BasicPad::digitClicked, this, &Calculator::digitClicked);
        disconnect(m_pCurrentPad, &BasicPad::operatorClicked, this, &Calculator::operatorClicked);
        disconnect(m_pCurrentPad, &BasicPad::equalClicked, this, &Calculator::equalClicked);
        disconnect(m_pCurrentPad, &BasicPad::controlClicked, this, nullptr);
        disconnect(m_pScientificPad, &ScientificPad::squareClicked, this, &Calculator::handleSquare);
        disconnect(m_pScientificPad, &ScientificPad::sqrtClicked, this, &Calculator::handleSqrt);
        disconnect(m_pScientificPad, &ScientificPad::absClicked, this, &Calculator::handleAbs);
   }
    // 根据模式切换显示的键盘
    if (m_currentMode == "standard") 
    {
        m_pCurrentPad = m_pStandardPad;
        m_pKeyboardStack->setCurrentWidget(m_pStandardPad);
    }
    else 
    {
        m_pCurrentPad = m_pScientificPad;
        m_pKeyboardStack->setCurrentWidget(m_pScientificPad);
    }
    // 显示新键盘并连接所有信号
    connect(m_pCurrentPad, &BasicPad::digitClicked, this, &Calculator::digitClicked);
    connect(m_pCurrentPad, &BasicPad::operatorClicked, this, &Calculator::operatorClicked);
    connect(m_pCurrentPad, &BasicPad::equalClicked, this, &Calculator::equalClicked);
    connect(m_pCurrentPad, &BasicPad::controlClicked, this, [this](QString cmd) {
        if (cmd == "C") clearExpression();
        else if (cmd == "B") backspaceClicked();
        });
    connect(m_pScientificPad, &ScientificPad::squareClicked, this, &Calculator::handleSquare);
    connect(m_pScientificPad, &ScientificPad::sqrtClicked, this, &Calculator::handleSqrt);
    connect(m_pScientificPad, &ScientificPad::absClicked, this, &Calculator::handleAbs);

    // 强制刷新布局
    m_pKeyboardStack->currentWidget()->layout()->activate();
    update();
}

bool Calculator::isNumber(const QString &expr)
{
    // 正则表达式匹配整数、小数、科学计数法
    QRegExp regx("^[+-]?(\\d+(\\.\\d+)?|\\.\\d+)([eE][+-]?\\d+)?$");
    return regx.exactMatch(expr);
}

void Calculator::handleSquare() 
{
    if (isNumber(m_expression))
    {
        double num = m_expression.toDouble();
        QString originalExpr = m_expression;
        qDebug() << num * num;
        m_expression = QString::number(num * num); 
        updateDisplay();
        m_historyManager.addEntry("square("+originalExpr + ") = " + m_expression);
    }
    else 
    {
        QMessageBox::warning(this, "error", "expression is illegal");
    }
}

void Calculator::handleSqrt() 
{
    if (isNumber(m_expression))
    {
        double num = m_expression.toDouble();
        if (num < 0) 
        {
            QMessageBox::warning(this, "error", "expression is illegal");
            return;
        }
        QString originalExpr = m_expression;
        m_expression = QString::number(sqrt(num));
        updateDisplay();
        m_historyManager.addEntry("sqrt(" + originalExpr + ") = " + m_expression);
    }
    else
    {
        QMessageBox::warning(this, "error", "expression is illegal");
    }
}

void Calculator::handleAbs()
{
    if (isNumber(m_expression)) 
    {
        double num = m_expression.toDouble();
        QString originalExpr = m_expression;
        m_expression = QString::number(abs(num));
        updateDisplay();
        m_historyManager.addEntry("|" + originalExpr + " | = " + m_expression);
    }
    else 
    {
        QMessageBox::warning(this, "error", "expression is illegal");
    }
}
