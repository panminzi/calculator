#pragma once
#ifndef NUMBERPAD_H
#define NUMBERPAD_H

#include <QWidget>

class NumberPad : public QWidget
{
    Q_OBJECT
public:
    explicit NumberPad(QWidget* parent = nullptr);

signals:
    void digitClicked(QString digit);
    void operatorClicked(QString op);
    void equalClicked();

private:
    void createButtons();
};
#endif // NUMBERPAD_H
