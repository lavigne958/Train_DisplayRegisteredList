#ifndef CSVREADER_H
#define CSVREADER_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFile>

#include "competitor.h"

class CSVReader
{
public:
    static QList<Competitor> getCompetitors(QString fileName, QStringList headers);
    static QStringList getHeader(QString fileName);
};

#endif // CSVREADER_H
