// topbar.h
#ifndef TOPBAR_H
#define TOPBAR_H

#include <QWidget>
#include <QMenu>
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
    void modeChanged(const QString& mode);  // 新增模式切换信号


private slots:
    void showModeMenu();  // 新增菜单显示槽函数

private:
    void setupUI();
    void createModeMenu();  // 新增菜单创建方法
    QPushButton* m_pMenuBtn;
    QPushButton* m_pHistoryBtn;
    QHBoxLayout* m_pLayout;
    QMenu* m_pModeMenu;         // 新增模式菜单
    QString m_currentMode = u8"标准";  // 当前模式
};

#endif // TOPBAR_H