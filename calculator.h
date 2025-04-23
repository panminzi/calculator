// calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include "historypopup.h"
#include "topbar.h"
#include "historymanager.h"
#include"numberpad.h"
#include< QStackedWidget>

class QTextEdit;
class QGridLayout;

class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget* parent = nullptr);
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
    void handleModeChange(const QString& mode);  // 新增模式处理槽函数
    //void updateHistoryDisplay();

private:
    void setupUI();
   // void createButtons();
    QPushButton* createButton(const QString& text, const char* member);
    void updatePopupLayout();
    bool eventFilter(QObject* obj, QEvent* event);

    // 计算逻辑相关
    bool isOperator(QChar c);
    double evaluateExpression(QString expr);
    bool hasPriority(QChar op1, QChar op2);
    void calculateStep(QStack<double>& nums, QStack<QChar>& ops);

    void setupStandardUI();     // 标准模式界面
    void setupScientificUI();   // 科学模式界面（占位实现）
    //void clearCurrentUI();      // 清理当前界面
    void setupModules();

    NumberPad* m_standardPad; // 标准模式键盘
    NumberPad* m_scientificPad; // 科学模式键盘
  
    Sidebar* m_pSideBar;
    TopBar* m_pTopBar;
    HistoryPopup* m_historyPopup;
    HistoryManager m_historyManager;
    QTextEdit* m_pDisplay;
    //QWidget* keyboardArea;
    QStackedWidget* m_keyboardStack; // 新增堆叠布局容器
    QWidget* m_overlay;
    QString m_calcErrorMsg;
    QString m_expression;
    bool m_hasCalcError = false;
    QString m_lastValidExpression;
    QWidget* m_pScientificPanel = nullptr;  // 科学模式面板
    void setupKeyboardLayout(); // 新增方法
    NumberPad* m_currentPad = nullptr; // 当前键盘实例
    QString  m_currentMode;
};

#endif // CALCULATOR_H