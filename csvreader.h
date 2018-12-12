#ifndef CSVREADER_H
#define CSVREADER_H

#include "reader.h"

class CSVReader : public Reader
{
public:
    CSVReader() = default;
    CSVReader(QString fileName) : Reader(fileName) {}
    ~CSVReader();
    QList<Competitor> getCompetitor(QStringList selectHeaders);
    QStringList getHeaders();
};

#endif // CSVREADER_H
