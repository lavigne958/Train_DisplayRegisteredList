#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString fileName;
    QStringList selectHeaders;

    void setup();
    void setupUiSettings();
    void fakeFillTree();
    void fillTree(const QString& fileName);
    QTreeWidgetItem *fillTreeEntry(const QString& text, QTreeWidgetItem *root);

private slots:
    void on_loadCompetitor_triggerred();
    void on_csvHeader_dialog_close(int status);
    void on_csvHeader_validate(QStringList headers);
};

#endif // MAINWINDOW_H
