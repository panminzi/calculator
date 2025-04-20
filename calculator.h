// calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include "historypopup.h"
#include "topbar.h"
#include "historymanager.h"

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
    void digitClicked();
    void operatorClicked();
    void equalClicked();
    void backspaceClicked();
    void clearExpression();
    void toggleHistoryWindow();
    //void updateHistoryDisplay();

private:
    void setupUI();
    void createButtons();
    QPushButton* createButton(const QString& text, const char* member);
    void updatePopupLayout();
    bool eventFilter(QObject* obj, QEvent* event);

    // º∆À„¬ﬂº≠œ‡πÿ
    bool isOperator(QChar c);
    double evaluateExpression(QString expr);
    bool hasPriority(QChar op1, QChar op2);
    void calculateStep(QStack<double>& nums, QStack<QChar>& ops);

    TopBar* m_topBar;
    HistoryPopup* m_historyPopup;
    HistoryManager m_historyManager;
    QTextEdit* m_pDisplay;
    QGridLayout* m_pButtonLayout;
    QWidget* m_overlay;
    QString m_calcErrorMsg;
    QString m_expression;
    bool m_hasCalcError = false;
    QString m_lastValidExpression;
};

#endif // CALCULATOR_H