#include "csvreader.h"
#include "competitor.h"

#include <QFile>
#include <QDebug>

QList<Competitor>
CSVReader::getCompetitors(const QString& fileName, QStringList headers)
{
    auto *file = new QFile(fileName);
    file->open(QFile::ReadOnly | QFile::Text);
    QList<Competitor> competitors;

    //dump first line
    QStringList firstLine = QString(file->readLine()).split("\t");
    QList<QPair<QString, int>> headersMapping;

    //go thru each column header found in the csv file
    for(int i = 0; i < headers.size(); ++i) {

        //cross it with each selected header given from the user
        for (int j = 0; j < firstLine.size(); ++j) {

            //if it matches, add it to the local mapping, and remove it from the headers list, so it is faster (may be ?)
            if (firstLine[j].compare(headers[i]) == 0) {
                headersMapping.append(QPair<QString, int>(headers[i], j));
            }
        }
    }

    while (!file->atEnd()) {
        QString line(file->readLine());

        if (line.isEmpty()) continue;

        QStringList splitLine = line.split("\t");
        QList<QPair<QString, QString>> competitorInfo;

        for (auto& h: headersMapping) {
            QPair<QString, QString> infos = QPair<QString, QString>(h.first, splitLine[h.second]);
            competitorInfo << infos;
        }

        Competitor c = Competitor(competitorInfo);

        competitors << c;
    }

    file->close();
    delete file;

    return competitors;
}

QStringList
CSVReader::getHeader(const QString& fileName)
{
    auto *file = new QFile(fileName);

    file->open(QFile::ReadOnly | QFile::Text);
    QString line = file->readLine();
    file->close();
    delete file;

    return line.split("\t");
}
