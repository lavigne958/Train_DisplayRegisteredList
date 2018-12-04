#ifndef COMPETITOR_H
#define COMPETITOR_H

#include <QString>
#include <QStringList>

class Competitor
{
public:
    Competitor();
    Competitor(QStringList);

    QStringList infos;
};

#endif // COMPETITOR_H
