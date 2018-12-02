#include "csvheader.h"
#include "ui_csvheader.h"

#include <QLabel>
#include <QComboBox>

#include <QDebug>

#define MAX_HEADER_SIZE 40

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
    this->ui->headersList->setTitle("List of found headers");
    this->stripHeader(MAX_HEADER_SIZE);

    for (int i = 0; i < this->headers.size(); ++i) {
        this->addUiHeaderChoice(i);
    }
}

CSVHeader::~CSVHeader()
{
    delete ui;
}

void
CSVHeader::addUiHeaderChoice(int pos)
{
    QLabel *headerLabel = nullptr;
    QComboBox *headersChoice = nullptr;

    QString lab = QString("Category ");
    lab.append(QString::number(pos));
    headerLabel = new QLabel(lab);

    headersChoice = new QComboBox();
    headersChoice->addItem("Do not use");
    headersChoice->addItems(this->headers);

    this->ui->verticalLayout->addWidget(headerLabel);
    this->ui->verticalLayout->addWidget(headersChoice);

    connect(headersChoice, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
            this, &CSVHeader::on_choice_changed);

    this->headerChoices << headersChoice;
}

void
CSVHeader::stripHeader(int maxStrSize)
{
    for (int i = 0; i < this->headers.size(); ++i) {
        if (headers[i].size() > maxStrSize) {
            headers[i].resize(maxStrSize);
        }
    }
}

void
CSVHeader::on_choice_changed(QString newText)
{
    qDebug() << "new selection: " << newText;
    for (auto cmbChoice: this->headerChoices) {
        if (cmbChoice->currentText().compare(newText) == 0) {
            qDebug() << "this is the current selection, do nothing";
            continue;
        }

        int pos = cmbChoice->findText(newText);
        qDebug() << "found it at pos: " << pos;
        cmbChoice->removeItem(pos);
    }
}
