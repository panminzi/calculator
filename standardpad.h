#ifndef ATANDARDPAD_H
#define ATANDARDPAD_H

#include "basicpad.h"
class StandardPad : public BasicPad
{
    Q_OBJECT
public:
    explicit StandardPad(QWidget *parent = nullptr);
    void moveBasicButtons(int offsetRow, int offsetColumn);
    void createSpecialButtons() override; 
    
};
#endif // !ATANDARDPAD_H


