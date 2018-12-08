#ifndef COMPETITOR_H
#define COMPETITOR_H

#include <QString>
#include <QStringList>

class Competitor
{
public:
    Competitor() = default;
    Competitor(QList<QPair<QString, QString>> infos);  //first: header, second: value for this competitor
    int getInfoCount();
    QStringList getHeaders();
    QString getInfo(int index);
    QString getInfo(const QString &header);

private:
    QList<QPair<QString, QString>> infos;

};

#endif // COMPETITOR_H
