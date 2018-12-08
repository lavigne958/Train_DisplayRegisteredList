#ifndef READER_H
#define READER_H

#include <QList>
#include <QStringList>
#include <QString>

#include "competitor.h"

class Reader
{
private:
    QString fileName;

public:
    Reader() = default;
    Reader(QString fileName) : fileName(fileName) {}
    virtual ~Reader();
    virtual QList<Competitor> getCompetitor(QStringList selectHeaders) = 0;
    virtual QStringList getHeaders() = 0;
};

#endif // READER_H
