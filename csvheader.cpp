#include "csvheader.h"
#include "ui_csvheader.h"

#include <QLabel>
#include <QComboBox>

#include <QDebug>

#define MAX_HEADER_SIZE 80

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

    //set ui dispay
    this->setWindowTitle("Headers order");
    this->ui->headersList->setTitle("List of found headers");
    //strip header that migh be too long
    this->stripHeader(MAX_HEADER_SIZE);
    this->updateInProgress = false;

    for (int i = 0; i < this->headers.size(); ++i) {
        QPair<QComboBox *, QString> headerSelect;

        //keep a pointer to the combobox
        headerSelect.first = this->addUiHeaderChoice(i);
        //keep the current selected header for this combobox
        headerSelect.second = "";

        this->selctorsHeaders.append(headerSelect);
    }
}

CSVHeader::~CSVHeader()
{
    delete ui;
}

QComboBox *
CSVHeader::addUiHeaderChoice(int pos)
{
    QLabel *headerLabel = nullptr;
    QComboBox *headersChoice = nullptr;

    QString lab = QString("Category ");
    lab.append(QString::number(pos));
    headerLabel = new QLabel(lab);

    headersChoice = new QComboBox();
    headersChoice->addItem("Do not use");
    headersChoice->addItems(QStringList(this->headers));

    this->ui->verticalLayout->addWidget(headerLabel);
    this->ui->verticalLayout->addWidget(headersChoice);

    connect(headersChoice, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
            this, &CSVHeader::on_choice_changed);

    return headersChoice;
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

    if (this->updateInProgress) {
        qDebug() << "triggered when updating, ignoring";
        return;
    }

    this->updateInProgress = true;

    qDebug() << "udpate in progress";
    //first find out which is the one that got updated:
    int i;
    QComboBox *updated = nullptr;
    QString head;
    QString previousHeader;

    for (i = 0; i < this->selctorsHeaders.size(); ++i) {
        updated = this->selctorsHeaders[i].first;
        head = this->selctorsHeaders[i].second;

        if (updated->currentText().compare(newText) == 0) {
            qDebug() << "Found the match combobox " << i;

            //found the comboBox that holds the new header, save the previous header
            previousHeader = this->selctorsHeaders[i].second;

            qDebug() << "previous header was: " << previousHeader;

            //update the map with the new value
            this->selctorsHeaders[i].second = newText;
            break;
        }
    }

    QComboBox *tmpCb;
    for (i = 0; i < this->selctorsHeaders.size(); ++i) {
        tmpCb = this->selctorsHeaders[i].first;

        if (!previousHeader.isEmpty()) {
            //if has something before then add it back in the list
            tmpCb->addItem(previousHeader);
        }

        if (tmpCb == updated) {
            //do not touch the one that got updated
            continue;
        }

        int pos = tmpCb->findText(newText);

        //if it is present, remove it
        if (pos != -1) {
            qDebug() << "cmb " << i << " has the header, remove it (" << pos << ")";
            tmpCb->removeItem(pos);
        } else {
            //if it is not present, add then
            qDebug() << "cmb " << i << " has not the header, add it then";
            tmpCb->addItem(newText);
        }
    }

    this->updateInProgress = false;
    qDebug() << "udpate finished";
}
