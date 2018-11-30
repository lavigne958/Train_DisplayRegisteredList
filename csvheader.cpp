#include "csvheader.h"
#include "ui_csvheader.h"

CSVHeader::CSVHeader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSVHeader)
{
    ui->setupUi(this);
}

CSVHeader::CSVHeader(QWidget *parent, QStringList headers):
    QDialog(parent),
    ui(new Ui::CSVHeader),
    headers(headers)
{
    ui->setupUi(this);

    this->setWindowTitle("Headers order");
    this->ui->headerListBox->setTitle("List of found headers");
    this->ui->headerOrderBox->setTitle("Ordered list of headers for the tree");

    this->ui->headersList->setDragEnabled(true);
    this->ui->headersOrder->viewport()->setAcceptDrops(true);

    for (auto header: headers) {
        this->ui->headersList->addItem(header);
    }
}

CSVHeader::~CSVHeader()
{
    delete ui;
}
