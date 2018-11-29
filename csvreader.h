#ifndef CSVREADER_H
#define CSVREADER_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFile>

class CSVReader
{
public:
    static void fillTree(QTreeWidget *tree);
    static enum {
        NAME = 1,
        FIRSTNAME = 2,
        TEAM = 3,
        LEVEL = 7,
        FIELD = 8,
        WEIGHT = 9
    } csv_fields;
private:
    static QTreeWidgetItem *findCreateItem(QString text, QTreeWidgetItem *root);
};

#endif // CSVREADER_H
