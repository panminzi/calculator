#pragma once
#ifndef BASICPAD_H
#define BASICPAD_H

#include <QWidget>
#include<QGridLayout>

class BasicPad : public QWidget
{
    Q_OBJECT
public:
    explicit BasicPad(QWidget *parent = nullptr);
    virtual void createSpecialButtons(); // �麯��������������չ���ⰴť
    virtual void moveBasicButtons(int offsetRow,int offsetColumn);
signals:
    void digitClicked(QString digit);
    void operatorClicked(QString op);
    void equalClicked();
    void controlClicked(QString cmd); // ���ڴ��� C/B �ȿ�������
protected:
    void createBaseButtons(); // �������ֺ�=��ť
    QGridLayout *m_pLayout; // protected �����������
};
#endif // BASICPAD_H
