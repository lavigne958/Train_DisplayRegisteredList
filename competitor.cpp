#include "competitor.h"

#include <QtDebug>



Competitor::Competitor(QList<QPair<QString, QString>> infos):
        infos(infos)
{
}

int
Competitor::getInfoCount()
{
    return this->infos.size();
}

QStringList
Competitor::getHeaders()
{
    QStringList headers;

    for (auto& info: this->infos) {
        headers << info.first;
    }

    return headers;
}

QString
Competitor::getInfo(int index)
{
    if (index < 0 || this->infos.size() <= index) {
        qDebug() << "index out of range: " << index;
        return QString();
    }

    return this->infos[index].second;
}

QString
Competitor::getInfo(const QString &header)
{
    for (auto info: this->infos) {
        if (info.first.compare(header) == 0) {
            return info.second;
        }
    }

    return QString();
}
