// topbar.h
#ifndef TOPBAR_H
#define TOPBAR_H

#include <QWidget>

class QPushButton;
class QHBoxLayout;

class TopBar : public QWidget
{
    Q_OBJECT
public:
    explicit TopBar(QWidget* parent = nullptr);

    void updateButtonSize(int size);
    QPushButton* historyButton() const;

signals:
    void historyClicked();

private:
    void setupUI();

    QPushButton* m_pHistoryBtn;
    QHBoxLayout* m_pLayout;
};

#endif // TOPBAR_H