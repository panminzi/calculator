#ifndef HISTORYPOPUP_H
#define HISTORYPOPUP_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

class HistoryPopup : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryPopup(QWidget *parent = nullptr);
    void updateHistory(const QStringList &history);
    void updateFontSize(int fontSize);

public slots:
    void showPopup();
    void hidePopup();

signals:
    void clearRequested();
    void closed();

private:
    void setupUI();
    QListWidget *m_pHistoryList;
    QPushButton *m_pClearHistoryBtn;
};
#endif // HISTORYPOPUP_H