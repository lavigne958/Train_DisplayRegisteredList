#ifndef CSVREADER_H
#define CSVREADER_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFile>

#include "competitor.h"

 enum csv_fields {
    NAME = 1,
    FIRSTNAME = 2,
    TEAM = 3,
    LEVEL = 7,
    FIELD = 8,
    WEIGHT = 9
};

class CSVReader
{
public:
    static QList<Competitor> getCompetitors(QString fileName);
    static QStringList getHeader(QString fileName);
};

#endif // CSVREADER_H
