#include "numberpad.h"
#include <QGridLayout>
#include <QPushButton>
#include<QDebug>

NumberPad::NumberPad(QWidget* parent)
    : QWidget(parent)
{
    m_layout = new QGridLayout(this);
    m_layout->setSpacing(5);
    m_layout->setContentsMargins(5, 5, 5, 5);  // 增加边距使布局更紧凑


    createBaseButtons();
    createSpecialButtons();

}

// 基础按钮：数字 0-9、. 和 =
void NumberPad::createBaseButtons()
{
    const QString baseButtons[4][3] = {
        {"7", "8", "9"},
        {"4", "5", "6"},
        {"1", "2", "3"},
        {"0", ".", "="}
    };

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 3; ++col) {
            QPushButton* btn = new QPushButton(baseButtons[row][col]);
            //btn->setMinimumSize(30, 30);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            if (row == 0 && col == 0)
                qDebug() << u8"基础键盘按钮" << btn->size();
            // 数字和小数点按钮
            if (baseButtons[row][col].contains(QRegExp("[0-9.]"))) {
                connect(btn, &QPushButton::clicked, [this, btn]() {
                    emit digitClicked(btn->text());
                    });
            }
            // 等号按钮
            else if (baseButtons[row][col] == "=") {
                connect(btn, &QPushButton::clicked, this, &NumberPad::equalClicked);
            }

            m_layout->addWidget(btn, row, col); // 基础按钮占据前4行
        }
    }

}

// 基类默认不添加特殊按钮（由子类实现）
void NumberPad::createSpecialButtons()
{
    // 空实现
}