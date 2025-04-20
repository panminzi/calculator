// topbar.cpp
#include "topbar.h"
#include <QHBoxLayout>
#include <QPushButton>

TopBar::TopBar(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
}

void TopBar::setupUI()
{
    m_pLayout = new QHBoxLayout(this);
    m_pLayout->setContentsMargins(0, 0, 0, 0);

    m_pHistoryBtn = new QPushButton;
    m_pHistoryBtn->setFlat(true);
    m_pHistoryBtn->setIcon(QIcon(":/calculator/images/icon_history.png"));
    m_pHistoryBtn->setStyleSheet(
        "QPushButton {"
        "  background: transparent; border: none; padding: 5px;"
        "}"
        "QPushButton:hover { background: rgba(0,0,0,0.1); border-radius: 16px; }"
    );

    connect(m_pHistoryBtn, &QPushButton::clicked, this, &TopBar::historyClicked);

    m_pLayout->addStretch();
    m_pLayout->addWidget(m_pHistoryBtn);
}

void TopBar::updateButtonSize(int size)
{
    m_pHistoryBtn->setFixedSize(size, size);
    m_pHistoryBtn->setIconSize(QSize(size - 8, size - 8));
}

QPushButton* TopBar::historyButton() const
{
    return m_pHistoryBtn;
}