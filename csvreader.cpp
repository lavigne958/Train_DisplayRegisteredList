#include "csvreader.h"
#include "competitor.h"

#include <QFile>
#include <QDebug>

QList<Competitor>
CSVReader::getCompetitors(QString fileName, QStringList headers)
{
    QFile *file = new QFile(fileName);
    file->open(QFile::ReadOnly);
    QList<Competitor> competitors;

    //dump first line
    QStringList firstLine = QString(file->readLine()).split("\t");
    QList<QPair<QString, int>> headersMapping;

    //go thru each column header found in the csv file
    for(int i = 0; i < firstLine.size(); ++i) {

        //cross it with each selected header given from the user
        for (int j = 0; j < headers.size(); ++j) {

            //if it matches, add it to the local mapping, and remove it from the headers list, so it is faster (may be ?)
            if (firstLine[i].compare(headers[j])) {
                headersMapping.append(QPair<QString, int>(headers[j], i));
                headers.removeAt(j);
            }
        }
    }

    while (!file->atEnd()) {
        QString line(file->readLine());

        if (line.isEmpty()) continue;

        QStringList splitLine = line.split("\t");
        QStringList competitorInfo;

        for (auto& h: headersMapping) {
            competitorInfo << splitLine[h.second];
        }

        Competitor c = Competitor(competitorInfo);

        competitors << c;
    }

    return competitors;
}

QStringList
CSVReader::getHeader(QString fileName)
{
    QFile *file = new QFile(fileName);

    file->open(QFile::ReadOnly);
    QString line = file->readLine();

    return line.split("\t");
}
