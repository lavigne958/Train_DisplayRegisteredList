#ifndef CSVHEADER_H
#define CSVHEADER_H

#include <QDialog>
#include <QList>
#include <QString>
#include <QStringList>
#include <QListWidgetItem>

namespace Ui {
class CSVHeader;
}

class CSVHeader : public QDialog
{
    Q_OBJECT

public:
    explicit CSVHeader(QWidget *parent = nullptr);
    explicit CSVHeader(QWidget *parent, QStringList headers);
    ~CSVHeader();

private:
    Ui::CSVHeader *ui;
    QList<QString> headers;
};

#endif // CSVHEADER_H
