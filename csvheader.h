#ifndef CSVHEADER_H
#define CSVHEADER_H

#include <QDialog>
#include <QList>
#include <QString>
#include <QStringList>
#include <QListWidgetItem>
#include <QComboBox>
#include <QAbstractButton>

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

signals:
    void validate(QStringList headers);

private:
    Ui::CSVHeader *ui;
    QStringList headers;
    QList<QPair<QComboBox *, QString>> selctorsHeaders;
    bool updateInProgress;

    QComboBox *addUiHeaderChoice(int pos);
    void stripHeader(int maxStrSize);

private slots:
    void on_choice_changed(QString newText);
    void on_ok_button_click(QAbstractButton *button);
};

#endif // CSVHEADER_H
