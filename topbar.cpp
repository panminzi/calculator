// topbar.cpp
#include "topbar.h"
#include <QHBoxLayout>
#include <QPushButton>

TopBar::TopBar(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
    createModeMenu();
}

void TopBar::setupUI()
{
    m_pLayout = new QHBoxLayout(this);
    m_pLayout->setContentsMargins(5, 0, 5, 0);  // 增加左右边距
    m_pLayout->setSpacing(10);

    // 新增菜单按钮
    m_pMenuBtn = new QPushButton;
    m_pMenuBtn->setFlat(true);
    m_pMenuBtn->setIcon(QIcon(":/calculator/images/icon_menu.png")); // 需要添加菜单图标资源
    m_pMenuBtn->setStyleSheet(
        "QPushButton {"
        "  background: transparent; border: none; padding: 5px;"
        "}"
        "QPushButton:hover { background: rgba(0,0,0,0.1); border-radius: 16px; }"
    );
    m_pLayout->addWidget(m_pMenuBtn);
    connect(m_pMenuBtn, &QPushButton::clicked, this, &TopBar::showModeMenu);

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
void TopBar::createModeMenu()
{
    m_pModeMenu = new QMenu(this);
    m_pModeMenu->setStyleSheet(
        "QMenu {"
        "  background: white;"
        "  border-radius: 8px;"
        "  padding: 5px 0;"
        "}"
        "QMenu::item {"
        "  padding: 8px 20px;"
        "  font-size: 14px;"
        "}"
        "QMenu::item:selected {"
        "  background: #F0F0F0;"
        "}"
    );

    QAction* standardAction = m_pModeMenu->addAction(u8"标准");
    QAction* scientificAction = m_pModeMenu->addAction(u8"科学");

    standardAction->setCheckable(true);
    scientificAction->setCheckable(true);
    standardAction->setChecked(true);

    connect(standardAction, &QAction::triggered, [this] {
        m_currentMode = u8"标准";
        emit modeChanged(m_currentMode);
        m_pModeMenu->actions()[0]->setChecked(true);
        m_pModeMenu->actions()[1]->setChecked(false);
        });

    connect(scientificAction, &QAction::triggered, [this] {
        m_currentMode = u8"科学";
        emit modeChanged(m_currentMode);
        m_pModeMenu->actions()[0]->setChecked(false);
        m_pModeMenu->actions()[1]->setChecked(true);
        });
}

void TopBar::showModeMenu()
{
    QPoint pos = m_pMenuBtn->mapToGlobal(QPoint(0, m_pMenuBtn->height()));
    m_pModeMenu->exec(pos);
}

// topbar.cpp
void TopBar::updateButtonSize(int size)
{
    // 菜单按钮
    m_pMenuBtn->setFixedSize(size, size);
    m_pMenuBtn->setIconSize(QSize(size - 8, size - 8));

    // 历史按钮
    m_pHistoryBtn->setFixedSize(size, size);
    m_pHistoryBtn->setIconSize(QSize(size - 8, size - 8));

    // 调整菜单字体
    QFont menuFont = m_pModeMenu->font();
    menuFont.setPixelSize(size * 0.6);
    m_pModeMenu->setFont(menuFont);
}
QPushButton* TopBar::historyButton() const
{
    return m_pHistoryBtn;
}
