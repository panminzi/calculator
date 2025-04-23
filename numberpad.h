#pragma once

#ifndef NUMBERPAD_H
#define NUMBERPAD_H
#include <QWidget>
#include<qgridlayout.h>

class NumberPad : public QWidget
{
    Q_OBJECT
public:
    explicit NumberPad(QWidget* parent = nullptr);
    virtual void createSpecialButtons(); // �麯��������������չ���ⰴť
signals:
    void digitClicked(QString digit);
    void operatorClicked(QString op);
    void equalClicked();
    void controlClicked(QString cmd); // �����źţ����ڴ��� C/B �ȿ�������
protected:
    QGridLayout* m_layout; // ��Ϊ protected �����������
    void createBaseButtons(); // �������ֺ�=��ť
};
#endif // NUMBERPAD_H
