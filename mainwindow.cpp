#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "csvreader.h"
#include <QDebug>

#define FILE "../test.tsv"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //this->fakeFillTree();
    this->fillTree();
    this->setup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::setup()
{
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
MainWindow::fillTree()
{
    QList<Competitor> competitors = CSVReader::getCompetitors(FILE);

     QTreeWidgetItem *root = nullptr;
    for (auto c: competitors) {
        //invisible root of the tree
        root = this->ui->competitorsTree->invisibleRootItem();
        //field:
        root = this->fillTreeEntry(c.field, root);
        //level:
        root = this->fillTreeEntry(c.level, root);
        //weight
        root = this->fillTreeEntry(c.weight, root);
        //team
        root = this->fillTreeEntry(c.team, root);
        //name
        root = this->fillTreeEntry(c.name, root);
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
