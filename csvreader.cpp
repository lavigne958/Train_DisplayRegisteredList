#include "csvreader.h"
#include "competitor.h"

#include <QFile>
#include <QDebug>

QList<Competitor>
CSVReader::getCompetitors(QString fileName)
{
    QFile *file = new QFile(fileName);

    qDebug() << "read file";
    file->open(QFile::ReadOnly);

    QList<Competitor> competitors;

    //dump first line
    file->readLine();

    while (!file->atEnd()) {
        QString line(file->readLine());

        if (line.isEmpty()) continue;

        QStringList splitLine = line.split("\t");
        qDebug() << "line: " << splitLine;
        Competitor c = Competitor(splitLine[NAME], splitLine[TEAM], splitLine[LEVEL], splitLine[WEIGHT], splitLine[FIELD]);

        competitors << c;
    }

    return competitors;
}
