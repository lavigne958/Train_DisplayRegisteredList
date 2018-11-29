#include "csvreader.h"
#include "competitor.h"

#include <QFile>
#include <QDebug>

#define FILE "../test.tsv"

void
CSVReader::fillTree(QTreeWidget *tree)
{
    QFile *file = new QFile(FILE);

    qDebug() << "read file";
    file->open(QFile::ReadOnly);

    //dump first line
    file->readLine();

    while (!file->atEnd()) {
        QString line(file->readLine());

        if (line.isEmpty()) continue;

        QStringList splitLine = line.split("\t");
        qDebug() << "line: " << splitLine;
        Competitor c = Competitor(splitLine[NAME], splitLine[TEAM], splitLine[LEVEL], splitLine[WEIGHT], splitLine[FIELD]);

        QTreeWidgetItem *root = tree->invisibleRootItem();

        //field:
        root = CSVReader::findCreateItem(c.field, root);
        //Level:
        root = CSVReader::findCreateItem(c.level, root);
        //wieght:
        root = CSVReader::findCreateItem(c.weight, root);
        //team
        root = CSVReader::findCreateItem(c.team, root);
        //name
        root = CSVReader::findCreateItem(c.name, root);
    }
}

QTreeWidgetItem *
CSVReader::findCreateItem(QString text, QTreeWidgetItem *root)
{
    QTreeWidgetItem *tmpChild = nullptr;

    int i;
    for (i = 0; i < root->childCount(); ++i) {
        tmpChild = root->child(i);

        //quick & dirty, found the entry in the tree
        if (tmpChild->text(0).compare(text) == 0) break;
    }

    if (i >= root->childCount()) {
        //did not find the entry
        tmpChild = new QTreeWidgetItem(QStringList(text));
        root->addChild(tmpChild);
    }


    return tmpChild;
}
