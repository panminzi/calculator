// sidebar.cpp
#include "sidebar.h"
#include <QVBoxLayout>
#include <QMouseEvent>

Sidebar::Sidebar(QWidget* parent)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint), m_parent(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);

    // 样式设置
    setStyleSheet(R"(
        background: white;
        border-right: 1px solid #E0E0E0;
        border-radius: 0 8px 8px 0;
    )");

    // 菜单列表
    m_pMenuList = new QListWidget(this);
    m_pMenuList->setStyleSheet(R"(
        QListWidget {
           background: white; border-radius: 8px 8px 0 0;
        }
        QListWidget::item {
            padding: 12px 24px;
            border-bottom: 1px solid #F0F0F0;
        }
        QListWidget::item:selected {
            background: #F5F5F5;
            color: #2196F3;
        }
    )");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_pMenuList);
    layout->setContentsMargins(0, 10, 0, 10);

    parent->installEventFilter(this);
    hide();
}

void Sidebar::addMenuItem(const QString& text, const QIcon& icon)
{
    QListWidgetItem* item = new QListWidgetItem(icon, text);
    item->setSizeHint(QSize(0, 40));
    m_pMenuList->addItem(item);
    connect(m_pMenuList, &QListWidget::itemClicked, [this](QListWidgetItem* item) {
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
    if (m_parent) {
        int sidebarWidth = m_parent->width() * 0.3;
        setFixedSize(sidebarWidth, m_parent->height());
        move(m_parent->mapToGlobal(QPoint(0, 0)));
    }
}

bool Sidebar::eventFilter(QObject* obj, QEvent* event)
{
    // 点击外部区域关闭
    if (event->type() == QEvent::MouseButtonPress && !this->isHidden()) {
        QPoint mousePos = static_cast<QMouseEvent*>(event)->globalPos();
        if (!geometry().contains(mousePos)) {
            hide();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}