#include "numberpad.h"
#include <QGridLayout>
#include <QPushButton>

NumberPad::NumberPad(QWidget* parent)
    : QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(this);
    layout->setSpacing(3);
    layout->setContentsMargins(0, 0, 0, 0);

    const QString buttons[4][3] = {
        {"7", "8", "9"},
        {"4", "5", "6"},
        {"1", "2", "3"},
        {"0", ".", "="}
    };

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 3; ++col) {
            QPushButton* btn = new QPushButton(buttons[row][col]);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            if (buttons[row][col] == "=") {
                connect(btn, &QPushButton::clicked, this, &NumberPad::equalClicked);
            }
            else if (buttons[row][col].contains(QRegExp("[0-9.]"))) {
                connect(btn, &QPushButton::clicked, [this, btn]() {
                    emit digitClicked(btn->text());
                    });
            }
            else {
                connect(btn, &QPushButton::clicked, [this, btn]() {
                    emit operatorClicked(btn->text());
                    });
            }

            layout->addWidget(btn, row, col);
        }
    }
}