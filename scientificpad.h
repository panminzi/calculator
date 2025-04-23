#pragma once
#include "numberpad.h"

class ScientificPad : public NumberPad {
    Q_OBJECT
public:
    explicit ScientificPad(QWidget* parent = nullptr);
    void createSpecialButtons() override; // 扩展科学按钮
};
