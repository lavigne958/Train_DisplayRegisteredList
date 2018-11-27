#include "csvreader.h"

#include <QFile>
#include <QDebug>

#define FILE "../test.csv"

void
CSVReader::fillTree(QTreeWidget *tree)
{
    QFile *file = new QFile(FILE);

    qDebug() << "read file";
    file->open(QFile::ReadOnly);
    for (int i = 0; i < 4; ++i) {
        QString line(file->readLine());

        if (line.isEmpty()) continue;

        QStringList splitLine = line.split(",");
        QList<QTreeWidgetItem *> fields = tree->findItems(splitLine[8], Qt::MatchExactly);

        QTreeWidgetItem *field = nullptr;
        if (fields.size() == 0) {
            //field not yet in the tree
            qDebug() << "new fiedl " << splitLine[8] << " create it";
            qDebug() << "found: " << fields.size();
            field = new QTreeWidgetItem(QStringList(splitLine[8]));
            tree->insertTopLevelItem(0, field);
        }
    }
}
