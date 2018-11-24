#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->fakeFillTree();
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
    this->ui->treeGroup->setTitle("Competitors tree");
    this->ui->infosGroup->setTitle("Competitor Info");

    this->ui->competitorsTree->setModel(this->treeModel);
}

void
MainWindow::fakeFillTree()
{
    this->treeModel = new QStringListModel();
    QStringList listA;
    QStringList listB;

    listA << "Alexandre" << "Baptiste" << "John";

    this->treeModel->setStringList(listA);
    this->treeModel->insertRow(4);

}
