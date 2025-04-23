#include "scientificpad.h"
#include <QPushButton>
#include<QDebug>

ScientificPad::ScientificPad(QWidget* parent) : NumberPad(parent) {
    createBaseButtons();
    createSpecialButtons(); // 在标准键盘基础上扩展
}

// scientificpad.cpp
void ScientificPad::createSpecialButtons() {

   // StandardPad::createSpecialButtons();

    const QString sciButtons[2][3] = {
        {"sin", "cos", "tan"},
        {"x", "y", "z"}
    };

    // 从第4行开始添加，避免与标准模式按钮重叠
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 3; ++col) {
            QPushButton* btn = new QPushButton(sciButtons[row][col]);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            if(row==0&&col==0)
            qDebug() << u8"科学键盘的按钮" << btn->size();
            connect(btn, &QPushButton::clicked, [this, btn]() {
                emit operatorClicked(btn->text());
                });
            m_layout->addWidget(btn, row + 4, col); // 第4行及以下
        }
    }
   // for (int row = 0; row < 6; ++row) {
   //    m_layout->setRowStretch(row, 1); // 所有行均匀拉伸
   // }
     //列拉伸保持原有设置
   // for (int col = 0; col < 4; ++col) {
   //     m_layout->setColumnStretch(col, 1);
   // }
}