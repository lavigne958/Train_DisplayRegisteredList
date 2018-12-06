#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvreader.h"
#include "csvheaderselector.h"

#include <QFileDialog>


#include <QDebug>

#define FILE "../test.tsv"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setup();
}

MainWindow::~MainWindow()
{
    this->rec_freeTreeItems(this->ui->competitorsTree->invisibleRootItem(), true);
    delete ui;
}

void
MainWindow::rec_freeTreeItems(QTreeWidgetItem *root, bool isRoot)
{
    if (root->childCount() > 0) {
        for (int i = 0; i < root->childCount(); ++i) {
            this->rec_freeTreeItems(root->child(0), false);
        }
    }

    if (!isRoot)
        delete root;
}

void
MainWindow::setup()
{
    this->fakeFillTree();
    this->setupUiSettings();
}

void
MainWindow::setupUiSettings()
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
MainWindow::fillTree(const QString& fileName)
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
    }
}

QTreeWidgetItem *
MainWindow::fillTreeEntry(const QString& text, QTreeWidgetItem *root)
{
    QTreeWidgetItem *tmpChild = nullptr;

    int i;
    for (i = 0; i < root->childCount(); ++i) {
        tmpChild = root->child(i);

        //quick & dirty, found the entry in the tree
        if (tmpChild->text(0).compare(text) == 0) break;
    }

    if (i >= root->childCount()) {
        //did not find the entry, freed at exit
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

    CSVHeaderSelector *headerDialog = new CSVHeaderSelector(this, headers);
    headerDialog->setModal(true);
    headerDialog->show();

    connect(headerDialog, &CSVHeaderSelector::finished,
            this, &MainWindow::on_csvHeader_dialog_close);

    connect(headerDialog, &CSVHeaderSelector::validate,
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
