// sidebar.h
#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QListWidget>

class Sidebar : public QWidget
{
    Q_OBJECT
public:
    explicit Sidebar(QWidget* parent = nullptr);

    void updatePosition();
    void addMenuItem(const QString& text, const QIcon& icon = QIcon());

signals:
    void itemClicked(const QString& text);
    void closed();

public slots:
    void showSidebar();
    void hideSidebar();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QListWidget* m_pMenuList;
    QWidget* m_parent;
};

#endif // SIDEBAR_H