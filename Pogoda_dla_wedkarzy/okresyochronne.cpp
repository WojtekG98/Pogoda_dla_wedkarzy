#include "okresyochronne.h"
#include "ui_okresyochronne.h"

OkresyOchronne::OkresyOchronne(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OkresyOchronne)
{
    ui->setupUi(this);
    ui->OkresyOchronneTekst->setReadOnly(true);
    ui->OkresyOchronneTekst->setText("Jest git");
}

OkresyOchronne::~OkresyOchronne()
{
    delete ui;
}
