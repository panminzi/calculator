#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QTextEdit>
#include <QStackedWidget>
#include <QGridLayout>

#include "standardpad.h"
#include "scientificpad.h"
#include "historypopup.h"
#include "topbar.h"
#include "historymanager.h"
#include "basicpad.h"

class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = nullptr);
    void connectSignals();
    void resetAfterError();
    void updateDisplay();
    void showResult(double result);
    void handleCalculationError(const QString& msg);

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void digitClicked(QString digit);
    void operatorClicked(QString op);
    void equalClicked();
    void backspaceClicked();
    void clearExpression();
    void toggleHistoryWindow();
    void toggleSideBar();
    void handleModeChange(const QString &mode);  //模式处理槽函数
    void handleSquare();   
    void handleSqrt();  
    void handleAbs();

private:
    void setupUI();
    void updatePopupLayout();
    void setupModules();
    void setupKeyboardLayout();
    bool eventFilter(QObject* obj, QEvent *event);
    // 计算逻辑相关
    bool isOperator(QChar c);
    bool isNumber(const QString &expr);
    double evaluateExpression(QString expr);
    bool hasPriority(QChar op1, QChar op2);
    void calculateStep(QStack<double> &nums, QStack<QChar> &ops);
    bool m_hasCalcError = false;
    QString m_calcErrorMsg;
    QString m_expression;
    QString m_lastValidExpression;
    QString  m_currentMode;
    HistoryManager m_historyManager;
    BasicPad *m_pCurrentPad = nullptr; // 当前键盘实例
    StandardPad *m_pStandardPad=nullptr; // 标准模式键盘
    ScientificPad *m_pScientificPad=nullptr; // 科学模式键盘
    Sidebar *m_pSideBar=nullptr;
    TopBar *m_pTopBar=nullptr;
    HistoryPopup *m_pHistoryPopup=nullptr;
    QTextEdit *m_pDisplay=nullptr;
    QStackedWidget *m_pKeyboardStack=nullptr; // 堆叠布局容器
    QWidget *m_pOverlay=nullptr;
};
#endif // CALCULATOR_H