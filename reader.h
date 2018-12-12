#ifndef READER_H
#define READER_H

#include <QList>
#include <QStringList>
#include <QString>

#include <qdebug.h>

#include "competitor.h"

class Reader
{
protected:
    QString fileName;

public:
    Reader() = default;
    Reader(QString& fileName)
    {
        this->fileName = fileName;
    }
    ~Reader()
    {
    }
    virtual QList<Competitor> getCompetitor(QStringList selectHeaders) = 0;
    virtual QStringList getHeaders() = 0;
};

#endif // READER_H
