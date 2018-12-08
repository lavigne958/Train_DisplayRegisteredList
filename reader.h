#ifndef READER_H
#define READER_H

#include <QList>
#include <QStringList>
#include <QString>

#include "competitor.h"

class Reader
{
public:
    Reader() = default;
    virtual ~Reader();
    static QList<Competitor> getCompetitor(QString fileName, QStringList selectHeaders) { return QList<Competitor>(); }
    static QStringList getHeaders(QString fileName) { return QStringList(); }
};

#endif // READER_H
