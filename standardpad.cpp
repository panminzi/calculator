#include <QPushButton>

#include "standardpad.h"

StandardPad::StandardPad(QWidget *parent): BasicPad(parent) 
{
    moveBasicButtons(1, 0);
    createSpecialButtons();
}
void StandardPad::moveBasicButtons(int offsetRow, int offsetColumn)
{
    for (int oldRow = 0; oldRow < 4; ++oldRow)
    {
        for (int col = 0; col < 3; ++col) 
        {
            QLayoutItem *item = m_pLayout->itemAtPosition(oldRow, col);
            if (item) 
            {
                QWidget *widget = item->widget();
                m_pLayout->removeWidget(widget);
                m_pLayout->addWidget(widget, oldRow + offsetRow, col+offsetColumn); 
            }
        }
    }
}

void StandardPad::createSpecialButtons() 
{
    const QString ops[] = { "+", "-", "*", "/" ,"(",")"};
    for (int i = 0; i < 6; ++i) 
    {
        QPushButton *btn = new QPushButton(ops[i]);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        if (i < 4)
        {
           m_pLayout->addWidget(btn, i + 1, 3);
           connect(btn, &QPushButton::clicked, [this, btn]() {
               emit operatorClicked(btn->text());
               });
        }   
        else if (i == 4)
        {
           m_pLayout->addWidget(btn, 0, 2);
           connect(btn, &QPushButton::clicked, [this, btn]() {
               emit operatorClicked("(");
               });
        } 
        else
        {
          m_pLayout->addWidget(btn, 0, 3);
          connect(btn, &QPushButton::clicked, [this, btn]() {
              emit operatorClicked(")");
              });
        }  
    }
    // 创建 C 和 B 按钮
    QPushButton *clearBtn = new QPushButton("clean");
    QPushButton *backBtn = new QPushButton("back");
    clearBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    backBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(clearBtn, &QPushButton::clicked, [this]() { emit controlClicked("C"); });
    connect(backBtn, &QPushButton::clicked, [this]() { emit controlClicked("B"); });
    m_pLayout->addWidget(clearBtn, 0, 0);
    m_pLayout->addWidget(backBtn, 0, 1);
}