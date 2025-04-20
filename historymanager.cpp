// historymanager.cpp
#include "historymanager.h"

HistoryManager::HistoryManager(QObject* parent)
    : QObject(parent)
{}

void HistoryManager::addEntry(const QString& entry)
{
    m_history.prepend(entry);
    if (m_history.size() > MAX_HISTORY) m_history.removeLast();
    emit historyChanged();
}

void HistoryManager::clear()
{
    m_history.clear();
    emit historyChanged();
}

QStringList HistoryManager::history() const
{
    return m_history;
}