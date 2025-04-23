#include <QPushButton>

#include "scientificpad.h"

ScientificPad::ScientificPad(QWidget* parent) 
    : BasicPad(parent)
{
    moveBasicButtons(1, 0);
    createSpecialButtons(); 
}

void ScientificPad::moveBasicButtons(int offsetRow,int offsetColumn)
{
    // 将基础键盘下移
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 3; ++col) {
            QLayoutItem* item = m_pLayout->itemAtPosition(row, col);
            if (item) {
                QWidget* widget = item->widget();
                m_pLayout->removeWidget(widget);
                m_pLayout->addWidget(widget, row + offsetRow, col+offsetColumn); 
            }
        }
    }

}

void ScientificPad::createSpecialButtons() 
{
    const QString ops[] = { "+", "-", "*", "/" };
    for (int i = 0; i < 4; ++i)
    {
        QPushButton *btn = new QPushButton(ops[i]);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        {
            m_pLayout->addWidget(btn, i + 1, 3);
            connect(btn, &QPushButton::clicked, [this, btn]() {
                emit operatorClicked(btn->text());
                });
        }
        // 创建 C 按钮
        QPushButton* clearBtn = new QPushButton("clean");
        clearBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(clearBtn, &QPushButton::clicked, [this]() { emit controlClicked("C"); });
        // 添加科学按钮
        QPushButton* squareBtn = new QPushButton("square");
        QPushButton* sqrtBtn = new QPushButton("sqrt");
        QPushButton* absBtn = new QPushButton("abs");
        squareBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sqrtBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        absBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        clearBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        // 连接按钮到独立信号
        connect(squareBtn, &QPushButton::clicked, this, &ScientificPad::squareClicked);
        connect(sqrtBtn, &QPushButton::clicked, this, &ScientificPad::sqrtClicked);
        connect(absBtn, &QPushButton::clicked, this, &ScientificPad::absClicked);
        m_pLayout->addWidget(clearBtn, 0, 0);
        m_pLayout->addWidget(squareBtn, 0, 2);
        m_pLayout->addWidget(sqrtBtn, 0, 1);
        m_pLayout->addWidget(absBtn, 0, 3);
    }
}