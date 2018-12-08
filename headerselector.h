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
class HeaderSelector;
}

class HeaderSelector : public QDialog
{
    Q_OBJECT

public:
    explicit HeaderSelector(QWidget *parent = nullptr);
    explicit HeaderSelector(QWidget *parent, QStringList headers);
    ~HeaderSelector();

signals:
    void validate(QStringList headers);

private:
    Ui::HeaderSelector *ui;
    QStringList headers;
    QList<QPair<QComboBox *, QString>> selctorsHeaders;
    bool updateInProgress;

    QComboBox *addUiHeaderChoice(int pos);
    void stripHeader(int maxStrSize);

private slots:
    void on_choice_changed(const QString &newText);
    void on_ok_button_click(QAbstractButton *button);
};

#endif // CSVHEADER_H
