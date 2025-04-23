#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPushButton>

#include "sidebar.h"

Sidebar::Sidebar(QWidget *parent)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint)
    , m_parent(parent)
{
    setStyleSheet(R"(
        QWidget {
            background: white;
            border: none;
            margin: 0;
            padding: 0;
        }
    )");
    // 添加关闭按钮
    QPushButton *closeBtn = new QPushButton(this);
    closeBtn->setIcon(QIcon(":/calculator/images/icon_menu.png"));
    closeBtn->setFlat(true);
    closeBtn->setFixedSize(32, 32);
    closeBtn->setStyleSheet(R"(
        QPushButton {
            background: white;
            border: none;
            padding: 5px;
        }
        QPushButton:hover {
            background: rgba(0,0,0,0.1);
            border-radius: 16px;
        }
    )");
    connect(closeBtn, &QPushButton::clicked, this, &Sidebar::hideSidebar);
    // 调整布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* headerLayout = new QHBoxLayout;
    headerLayout->addWidget(closeBtn, 0, Qt::AlignLeft);
    headerLayout->addStretch();
    mainLayout->addLayout(headerLayout);
    mainLayout->setContentsMargins(5, 5, 5, 5); 
    // 菜单列表
    m_pMenuList = new QListWidget(this);
    m_pMenuList->setStyleSheet(R"(
    QListWidget {
        background: white;
        border: none;
        margin: 0;
        padding: 0;
        outline: none;
    }
    QListWidget::item {
        background: white;
        border: none;
        margin: 0;
        padding: 5px 5px;
    }
    QListWidget::item:hover {
        background: #F5F5F5;
    }
    QListWidget::item:selected {
        background: #E0E0E0;
        color: #2196F3;
    }
    QScrollBar:vertical {
        width: 6px;
        background: white;
    }
    QScrollBar::handle:vertical {
        background: #E0E0E0;
        border-radius: 3px;
    }
)");
    mainLayout->addWidget(m_pMenuList);
    mainLayout->setContentsMargins(5, 5, 5, 5); 
    parent->installEventFilter(this);
    hide();
}

void Sidebar::addMenuItem(const QString &text, const QIcon &icon)
{
    QListWidgetItem *item = new QListWidgetItem(icon, text);
    item->setSizeHint(QSize(0, 40));
    m_pMenuList->addItem(item);
    connect(m_pMenuList, &QListWidget::itemClicked, [this](QListWidgetItem *item) {
        emit itemClicked(item->text());
        hide();
        });
}

void Sidebar::showSidebar()
{
    updatePosition();
    show();
    raise();
}

void Sidebar::hideSidebar()
{
    hide();
    emit closed();
}

void Sidebar::updatePosition()
{
    if (m_parent)
    {
        int sidebarWidth = m_parent->width() * 0.35;
        setFixedSize(sidebarWidth, m_parent->height());
        move(m_parent->mapToGlobal(QPoint(0, 0)));
    }
}

bool Sidebar::eventFilter(QObject *obj, QEvent *event)
{
    // 点击外部区域关闭
    if (event->type() == QEvent::MouseButtonPress && !this->isHidden()) 
    {
        QPoint mousePos = static_cast<QMouseEvent*>(event)->globalPos();
        if (!geometry().contains(mousePos)) 
        {
            hide();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}