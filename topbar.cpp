// topbar.cpp
#include "topbar.h"
#include <QHBoxLayout>

TopBar::TopBar(Sidebar* sidebar, QWidget* parent)
    : QWidget(parent), m_pSideBar(sidebar)
{
    setupUI();
}

void TopBar::setupUI()
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(10, 0, 10, 0);
    mainLayout->setSpacing(15);

    // 菜单按钮
    m_pMenuBtn = new QPushButton;
    m_pMenuBtn->setFlat(true);
    m_pMenuBtn->setIcon(QIcon(":/calculator/images/icon_menu.png"));
    m_pMenuBtn->setStyleSheet(R"(
        QPushButton {
            background: transparent;
            padding: 5px;
            border-radius: 16px;
        }
        QPushButton:hover {
            background: rgba(0,0,0,0.1);
        }
    )");
    connect(m_pMenuBtn, &QPushButton::clicked, this,&TopBar::showModeMenu);
    //connect(m_pMenuBtn, &QPushButton::clicked, [this] {
    //    m_pSideBar->showSidebar();
     //   });
    // 历史按钮
    m_pHistoryBtn = new QPushButton;
    m_pHistoryBtn->setFlat(true);
    m_pHistoryBtn->setIcon(QIcon(":/calculator/images/icon_history.png"));
    m_pHistoryBtn->setStyleSheet(m_pMenuBtn->styleSheet());
    connect(m_pHistoryBtn, &QPushButton::clicked,
        this, &TopBar::historyClicked);

    mainLayout->addWidget(m_pMenuBtn);
    mainLayout->addStretch();
    mainLayout->addWidget(m_pHistoryBtn);
}

void TopBar::updateButtonSize(int size)
{
    m_pMenuBtn->setFixedSize(size, size);
    m_pMenuBtn->setIconSize(QSize(size - 8, size - 8));
    m_pHistoryBtn->setFixedSize(size, size);
    m_pHistoryBtn->setIconSize(QSize(size - 8, size - 8));
}

QPushButton* TopBar::historyButton() const
{
    return m_pHistoryBtn;
}