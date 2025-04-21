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
    void modeChanged(const QString& mode);  // ����ģʽ�л��ź�


private slots:
    void showModeMenu();  // �����˵���ʾ�ۺ���

private:
    void setupUI();
    void createModeMenu();  // �����˵���������
    QPushButton* m_pMenuBtn;
    QPushButton* m_pHistoryBtn;
    QHBoxLayout* m_pLayout;
    QMenu* m_pModeMenu;         // ����ģʽ�˵�
    QString m_currentMode = u8"��׼";  // ��ǰģʽ
};

#endif // TOPBAR_H