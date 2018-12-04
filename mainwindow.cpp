#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvreader.h"
#include "csvheader.h"

#include <QFileDialog>


#include <QDebug>

#define FILE "../test.tsv"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setup();

    this->on_loadCompetitor_triggerred();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::setup()
{
    //this->fakeFillTree();
    this->setupUi();
}

void
MainWindow::setupUi()
{
    // group boxes
    this->ui->treeGroup->setTitle("Competitors tree");
    this->ui->infosGroup->setTitle("Competitor Info");

    //left group box => compeptitors list
    this->ui->competitorsTree->setColumnCount(1);
    this->ui->competitorsTree->setHeaderLabel("Competitors");

    connect(this->ui->actionLoad_Competitors, &QAction::triggered,
            this, &MainWindow::on_loadCompetitor_triggerred);
}

void
MainWindow::fakeFillTree()
{
    this->ui->competitorsTree->insertTopLevelItem(0, new QTreeWidgetItem(QStringList(QString("A"))));
    this->ui->competitorsTree->insertTopLevelItem(1, new QTreeWidgetItem(QStringList(QString("B"))));
    this->ui->competitorsTree->insertTopLevelItem(2, new QTreeWidgetItem(QStringList(QString("C"))));

    QTreeWidgetItem *item = this->ui->competitorsTree->topLevelItem(0);
    item->insertChild(0, new QTreeWidgetItem(QStringList(QString("A1"))));
    item->insertChild(0, new QTreeWidgetItem(QStringList(QString("A2"))));

    item = this->ui->competitorsTree->topLevelItem(1);
    item->insertChild(0, new QTreeWidgetItem(QStringList(QString("B1"))));
    item->insertChild(0, new QTreeWidgetItem(QStringList(QString("B2"))));
}

void
MainWindow::fillTree(QString fileName)
{
    QList<Competitor> competitors = CSVReader::getCompetitors(fileName, this->selectHeaders);

     QTreeWidgetItem *root = nullptr;
    for (auto c: competitors) {
        //invisible root of the tree
        root = this->ui->competitorsTree->invisibleRootItem();

        QStringList headerToInsert = c.getHeaders();

        for (auto& header: headerToInsert) {
            root = this->fillTreeEntry(c.getInfo(header), root);
        }

        /*
        //field:
        root = this->fillTreeEntry(c.infos[0], root);
        //level:
        root = this->fillTreeEntry(c.infos[1], root);
        //weight
        root = this->fillTreeEntry(c.infos[2], root);
        //team
        root = this->fillTreeEntry(c.infos[3], root);
        //name
        root = this->fillTreeEntry(c.infos[4], root);
        */
    }
}

QTreeWidgetItem *
MainWindow::fillTreeEntry(QString text, QTreeWidgetItem *root)
{
    QTreeWidgetItem *tmpChild = nullptr;

    int i;
    for (i = 0; i < root->childCount(); ++i) {
        tmpChild = root->child(i);

        //quick & dirty, found the entry in the tree
        if (tmpChild->text(0).compare(text) == 0) break;
    }

    if (i >= root->childCount()) {
        //did not find the entry
        tmpChild = new QTreeWidgetItem(QStringList(text));
        root->addChild(tmpChild);
    }


    return tmpChild;
}

void
MainWindow::on_loadCompetitor_triggerred()
{
    this->fileName = QFileDialog::getOpenFileName(this,
                                                    "Open competitors TSV File",
                                                    "/home/alexandre/projects/",
                                                    "Tabulated Separated Value file (*.tsv)");

    if (this->fileName.isEmpty()) {
        //did not choose to open a file
        return;
    }

    QStringList headers = CSVReader::getHeader(this->fileName);

    CSVHeader *headerDialog = new CSVHeader(this, headers);
    headerDialog->setModal(true);
    headerDialog->show();

    connect(headerDialog, &CSVHeader::finished,
            this, &MainWindow::on_csvHeader_dialog_close);

    connect(headerDialog, &CSVHeader::validate,
            this, &MainWindow::on_csvHeader_validate);
}

void
MainWindow::on_csvHeader_validate(QStringList headers)
{
    this->selectHeaders = headers;
}

void
MainWindow::on_csvHeader_dialog_close(int status)
{
    if (status == 1) {
        this->fillTree(this->fileName);
    }
}
