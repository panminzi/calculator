
#pragma once
#include "numberpad.h"

class StandardPad : public NumberPad {
    Q_OBJECT
public:
    explicit StandardPad(QWidget* parent = nullptr);
    void createSpecialButtons() override; // ʵ�ֻ����麯��
};
