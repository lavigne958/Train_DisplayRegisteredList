#ifndef CSVHEADER_H
#define CSVHEADER_H

#include <QDialog>
#include <QList>
#include <QString>
#include <QStringList>
#include <QListWidgetItem>
#include <QComboBox>

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
    QList<QComboBox *> headerChoices;

    void addUiHeaderChoice(int pos);
    void stripHeader(int maxStrSize);

private slots:
    void on_choice_changed(QString newText);
};

#endif // CSVHEADER_H
