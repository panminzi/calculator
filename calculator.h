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
    void handleModeChange(const QString& mode);  // ����ģʽ����ۺ���
    //void updateHistoryDisplay();

private:
    void setupUI();
   // void createButtons();
    QPushButton* createButton(const QString& text, const char* member);
    void updatePopupLayout();
    bool eventFilter(QObject* obj, QEvent* event);

    // �����߼����
    bool isOperator(QChar c);
    double evaluateExpression(QString expr);
    bool hasPriority(QChar op1, QChar op2);
    void calculateStep(QStack<double>& nums, QStack<QChar>& ops);

    void setupStandardUI();     // ��׼ģʽ����
    void setupScientificUI();   // ��ѧģʽ���棨ռλʵ�֣�
    //void clearCurrentUI();      // ����ǰ����
    void setupModules();

    NumberPad* m_standardPad; // ��׼ģʽ����
    NumberPad* m_scientificPad; // ��ѧģʽ����
  
    Sidebar* m_pSideBar;
    TopBar* m_pTopBar;
    HistoryPopup* m_historyPopup;
    HistoryManager m_historyManager;
    QTextEdit* m_pDisplay;
    //QWidget* keyboardArea;
    QStackedWidget* m_keyboardStack; // �����ѵ���������
    QWidget* m_overlay;
    QString m_calcErrorMsg;
    QString m_expression;
    bool m_hasCalcError = false;
    QString m_lastValidExpression;
    QWidget* m_pScientificPanel = nullptr;  // ��ѧģʽ���
    void setupKeyboardLayout(); // ��������
    NumberPad* m_currentPad = nullptr; // ��ǰ����ʵ��
    QString  m_currentMode;
};

#endif // CALCULATOR_H