#ifndef CSVREADER_H
#define CSVREADER_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFile>

class CSVReader
{
public:
    static void fillTree(QTreeWidget *tree);
};

#endif // CSVREADER_H
