#include "pomoc.h"
#include "ui_pomoc.h"

Pomoc::Pomoc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pomoc)
{
    ui->setupUi(this);
}

Pomoc::~Pomoc()
{
    delete ui;
}
