#ifndef COMPETITOR_H
#define COMPETITOR_H

#include <QString>

class Competitor
{
public:
    Competitor();
    Competitor(QString name, QString team, QString level, QString weight, QString field);

    QString name;
    QString team;
    QString level;
    QString weight;
    QString field;
};

#endif // COMPETITOR_H
