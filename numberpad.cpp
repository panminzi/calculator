#include "numberpad.h"
#include <QGridLayout>
#include <QPushButton>
#include<QDebug>

NumberPad::NumberPad(QWidget* parent)
    : QWidget(parent)
{
    m_layout = new QGridLayout(this);
    m_layout->setSpacing(5);
    m_layout->setContentsMargins(5, 5, 5, 5);  // ���ӱ߾�ʹ���ָ�����


    createBaseButtons();
    createSpecialButtons();

}

// ������ť������ 0-9��. �� =
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
                qDebug() << u8"�������̰�ť" << btn->size();
            // ���ֺ�С���㰴ť
            if (baseButtons[row][col].contains(QRegExp("[0-9.]"))) {
                connect(btn, &QPushButton::clicked, [this, btn]() {
                    emit digitClicked(btn->text());
                    });
            }
            // �ȺŰ�ť
            else if (baseButtons[row][col] == "=") {
                connect(btn, &QPushButton::clicked, this, &NumberPad::equalClicked);
            }

            m_layout->addWidget(btn, row, col); // ������ťռ��ǰ4��
        }
    }

}

// ����Ĭ�ϲ�������ⰴť��������ʵ�֣�
void NumberPad::createSpecialButtons()
{
    // ��ʵ��
}