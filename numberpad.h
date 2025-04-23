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
    virtual void createSpecialButtons(); // 虚函数，用于子类扩展特殊按钮
signals:
    void digitClicked(QString digit);
    void operatorClicked(QString op);
    void equalClicked();
    void controlClicked(QString cmd); // 新增信号，用于传递 C/B 等控制命令
protected:
    QGridLayout* m_layout; // 改为 protected 便于子类访问
    void createBaseButtons(); // 基础数字和=按钮
};
#endif // NUMBERPAD_H
