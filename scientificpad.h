#ifndef SCIENTIFICPAD_H
#define SCIENTIFICPAD_H

#include "basicpad.h"

class ScientificPad : public BasicPad 
{
    Q_OBJECT
public:
    explicit ScientificPad(QWidget *parent = nullptr);
    void moveBasicButtons(int offsetRow, int offsetColumn);
    void createSpecialButtons() override; 
signals:
    void squareClicked();  
    void sqrtClicked();   
    void absClicked();      
};
#endif // SCIENTIFICPAD_H


