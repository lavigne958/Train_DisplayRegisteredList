#include "csvreader.h"
#include "competitor.h"

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
        Competitor c = Competitor(splitLine[2], splitLine[4], splitLine[8], splitLine[10], splitLine[9]);

        QTreeWidgetItem *tmpItem = tree->itemAt(0, 0);

        while (tmpItem) {
            //the field alreay exists
            if (!tmpItem->text(0).compare(c.field)) break;
            tmpItem = tree->itemBelow(tmpItem);
        }

        if (!tmpItem) {
            tmpItem = new QTreeWidgetItem(QStringList(c.field));
            tree->insertTopLevelItem(0, tmpItem);
        } else {
            qDebug() << "error, should not be here ...";
        }

        //fiel is either new and created or alreay here and found

        tmpItem = tmpItem->child(0);
    }
}
