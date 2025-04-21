#ifndef TOPBAR_H
#define TOPBAR_H


#include <QWidget>
#include "sidebar.h"
#include<QPushButton>

class TopBar : public QWidget
{
    Q_OBJECT
public:
    explicit TopBar(Sidebar *sidebar, QWidget *parent = nullptr);
    
    void updateButtonSize(int size);
    QPushButton* historyButton() const;

signals:
    void historyClicked();
    void showModeMenu();

private:
    void setupUI();
    
    QPushButton *m_pMenuBtn;
    QPushButton *m_pHistoryBtn;
    Sidebar *m_pSideBar; // 使用模块化的侧边栏
};

#endif // TOPBAR_H
