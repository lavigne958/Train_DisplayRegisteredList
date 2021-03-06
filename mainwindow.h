#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QTreeWidgetItem>

#include "reader.h"

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
    Reader *reader;

    void setup();
    void setupUiSettings();
    void fakeFillTree();
    void fillTree();
    QTreeWidgetItem *fillTreeEntry(const QString& text, QTreeWidgetItem *root);
    void rec_freeTreeItems(QTreeWidgetItem *root, bool isRoot);

private slots:
    void on_loadCompetitor_triggerred();
    void on_header_dialog_validate(QStringList headers);
    void on_header_dialog_close(int status);
};

#endif // MAINWINDOW_H
