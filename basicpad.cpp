#include <QGridLayout>
#include <QPushButton>
#include "basicpad.h"

BasicPad::BasicPad(QWidget *parent)
    : QWidget(parent)
{
    m_pLayout = new QGridLayout(this);
    m_pLayout->setSpacing(5);
    m_pLayout->setContentsMargins(5, 5, 5, 5);  
    createBaseButtons();
    createSpecialButtons();

}
// 基础按钮：数字 0-9、. 和 =
void BasicPad::createBaseButtons()
{
    const QString baseButtons[4][3] = 
    {
        {"7", "8", "9"},
        {"4", "5", "6"},
        {"1", "2", "3"},
        {"0", ".", "="}
    };

    for (int row = 0; row < 4; ++row) 
    {
        for (int col = 0; col < 3; ++col) 
        {
            QPushButton *btn = new QPushButton(baseButtons[row][col]);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            if (baseButtons[row][col].contains(QRegExp("[0-9.]"))) 
            {
                connect(btn, &QPushButton::clicked, [this, btn]() {
                    emit digitClicked(btn->text());
                    });
            }
            else if (baseButtons[row][col] == "=") {
                connect(btn, &QPushButton::clicked, this, &BasicPad::equalClicked);
            }
            m_pLayout->addWidget(btn, row, col); 
        }
    }
}

void BasicPad::createSpecialButtons()
{
    // 空实现
}
void BasicPad::moveBasicButtons(int offsetRow,int offsetColumn)
{

}