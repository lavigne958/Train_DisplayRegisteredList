#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "competitor.h"
#include "csvreader.h"
#include "headerselector.h"

#include <QFileDialog>
#include <QVariant>
#include <QAction>
#include <QMessageBox>

//Needed for QVariant auto instanciate from Competitor class
Q_DECLARE_METATYPE(Competitor);

#include <QDebug>

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
    delete this->reader;
    delete ui;
}

/**
 * this recursive function check each node of the tree (DFS way).
 * Each node is looked at, if it has children, then each children is looked at.
 * just before returning from a child, the child is freed
 *
 * if (!isRoot) is here to make sure we do not try to free the fake root node
 *
 * @brief MainWindow::rec_freeTreeItems
 * @param root QTreeWidgetItem node of the tree that is currently being checked
 * @param isRoot bool true if it is the actual root of the tree, false otherwise
 */
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
    //this->fakeFillTree();
    this->setupUiSettings();

    this->reader = nullptr;
}

void
MainWindow::setupUiSettings()
{
    // group boxes titles
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

/**
 * @brief MainWindow::fillTree Fill the tree with the list of competitors comming from reader
 * @param fileName String file to open.
 */
void
MainWindow::fillTree()
{
    if (!this->reader) {
        qDebug() << "Can not fill tree, reader is null";
        return;
    }

    //This reader is only an interface, you can use the reader you like
    QList<Competitor> competitors = this->reader->getCompetitor(this->selectHeaders);

    QTreeWidgetItem *root = nullptr;
    for (auto& c: competitors) {
        //invisible root of the tree
        root = this->ui->competitorsTree->invisibleRootItem();

        QStringList headerToInsert = c.getHeaders();

        for (auto& header: headerToInsert) {
            root = this->fillTreeEntry(c.getInfo(header), root);
        }

        root->setData(0, 1, QVariant::fromValue(c));
    }
}

/**
 * @brief MainWindow::fillTreeEntry insert/find from a specific node the child
 * that matches @text
 * @param text String this is the text that represent the node of the tree
 * @param root QTreeWidgetItem actual node of the tree
 * @return QTreeWdigetItem newly created node or the matching node if found
 */
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

/**
 * @brief MainWindow::on_loadCompetitor_triggerred triggered when user click on File->loadFile
 */
void
MainWindow::on_loadCompetitor_triggerred()
{
    this->fileName = QFileDialog::getOpenFileName(this,
                                                    "Open competitors TSV File",
                                                    "/home/alexandre/projects/",
                                                    "Tabulated Separated Value file (*.tsv)");

    if (this->fileName.isEmpty()) {
        QMessageBox::warning(this, "Oops, can not continue", "No file has been selected.");
        return;
    }


    this->reader = new CSVReader(this->fileName);

    //from there you know that a file has been selected, its name is stored under this->fileName.
    // then you can fill the tree with the reader you like
    QStringList headers = this->reader->getHeaders();
    HeaderSelector *headerDialog = new HeaderSelector(this, headers);
    headerDialog->setModal(true);
    headerDialog->show();

    connect(headerDialog, &HeaderSelector::finished,
            this, &MainWindow::on_header_dialog_close);

    connect(headerDialog, &HeaderSelector::validate,
            this, &MainWindow::on_header_dialog_validate);
}

/**
 * @brief MainWindow::on_csvHeader_validate triggered when user clicks on "OK" on the secondary Dialog
 * @param headers QStringList list of headers from the csv that the user selected
 */
void
MainWindow::on_header_dialog_validate(QStringList headers)
{
    this->selectHeaders = headers;
}

/**
 * @brief MainWindow::on_csvHeader_dialog_close triggered when the dialog window closes
 * @param status int return status of the dialog 1 == ok
 */
void
MainWindow::on_header_dialog_close(int status)
{
    if (status == 1) {
        this->fillTree();
        return;
    }

    QMessageBox::warning(this, "Changing plans?", "The headers/key window closed unexpectidly, please load your faile again");
}
