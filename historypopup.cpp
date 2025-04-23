#include <QPushButton>
#include <QVBoxLayout>

#include "historypopup.h"

HistoryPopup::HistoryPopup(QWidget *parent)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint)
{
    setupUI();
}

void HistoryPopup::setupUI()
{
    setStyleSheet("background: white; border-radius: 8px 8px 0 0;");
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    m_pHistoryList = new QListWidget;
    m_pHistoryList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pClearHistoryBtn = new QPushButton("clear history");
    m_pClearHistoryBtn->setFixedHeight(50);
    m_pClearHistoryBtn->setStyleSheet(
        "QPushButton {"
        "  background: #FF6666; color: white; border: none;"
        "  font-size: 16px; border-radius: 0 0 8px 8px;"
        "}"
        "QPushButton:hover { background: #FF4444; }"
    );
    layout->addWidget(m_pHistoryList, 8);
    layout->addWidget(m_pClearHistoryBtn, 2);
    connect(m_pClearHistoryBtn, &QPushButton::clicked, this, &HistoryPopup::clearRequested);
}

void HistoryPopup::showPopup()
{
    QWidget *parent = qobject_cast<QWidget*>(this->parent());
    if (!parent)
        return;
    QRect rect = parent->geometry();
    rect.setTop(rect.bottom() - parent->height() / 2);
    setGeometry(rect);
    show();
}

void HistoryPopup::hidePopup()
{
    hide();
    emit closed();
}

void HistoryPopup::updateHistory(const QStringList &history)
{
    m_pHistoryList->clear();
    m_pHistoryList->addItems(history);
}

void HistoryPopup::updateFontSize(int fontSize)
{
    QFont font = m_pHistoryList->font();
    font.setPixelSize(fontSize);
    m_pHistoryList->setFont(font);
    m_pHistoryList->setStyleSheet(
        QString("QListWidget::item { height: %1px; }").arg(fontSize + 4)
    );
}