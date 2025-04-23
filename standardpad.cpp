#include "standardpad.h"
#include <QPushButton>
#include<QDebug>

StandardPad::StandardPad(QWidget* parent) : NumberPad(parent) {
    createBaseButtons();
    createSpecialButtons();
}

void StandardPad::createSpecialButtons() {
    const QString ops[] = { "+", "-", "*", "/" };
    for (int i = 0; i < 4; ++i) {
        QPushButton* btn = new QPushButton(ops[i]);
       // btn->setMinimumSize(30, 30);          // ͳһ��С�ߴ�
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        if (i == 0)
        qDebug() <<u8"��׼���̵İ�ť"<< btn->size();
        connect(btn, &QPushButton::clicked, [this, btn]() {
            emit operatorClicked(btn->text());
            });
        m_layout->addWidget(btn, i, 3);
    }

    // ���� C �� B ��ť
    QPushButton* clearBtn = new QPushButton("C");
    QPushButton* backBtn = new QPushButton("B");

    clearBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
 
    backBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(clearBtn, &QPushButton::clicked, [this]() { emit controlClicked("C"); });
    connect(backBtn, &QPushButton::clicked, [this]() { emit controlClicked("B"); });

    m_layout->addWidget(clearBtn, 4, 0);
    m_layout->addWidget(backBtn, 4, 1);
    // ��̬������������׼ģʽ��5�У�
    //for (int row = 0; row < 5; ++row) {
    //    m_layout->setRowStretch(row, 1); // ����5�е��������
  //  }
   // for (int col = 0; col < 4; ++col) {
   //     m_layout->setColumnStretch(col, 1); // 4�о�������
   // }
}