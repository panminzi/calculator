#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QObject>
#include <QStringList>

class HistoryManager : public QObject
{
    Q_OBJECT
public:
    explicit HistoryManager(QObject *parent = nullptr);

    void addEntry(const QString &entry);
    void clear();
    QStringList history() const;
signals:
    void historyChanged();
private:
    QStringList m_history;
    static const int MAX_HISTORY = 20;
};

#endif // HISTORYMANAGER_H