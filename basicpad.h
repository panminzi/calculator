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
    virtual void createSpecialButtons(); // 虚函数，用于子类扩展特殊按钮
    virtual void moveBasicButtons(int offsetRow,int offsetColumn);
signals:
    void digitClicked(QString digit);
    void operatorClicked(QString op);
    void equalClicked();
    void controlClicked(QString cmd); // 用于传递 C/B 等控制命令
protected:
    void createBaseButtons(); // 基础数字和=按钮
    QGridLayout *m_pLayout; // protected 便于子类访问
};
#endif // BASICPAD_H
