#include "glowneokno.h"
#include "ui_glowneokno.h"
#include "pomoc.h"

GlowneOkno::GlowneOkno(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GlowneOkno)
{
    ui->setupUi(this);
}

GlowneOkno::~GlowneOkno()
{
    delete ui;
}


void GlowneOkno::on_actionWy_wietl_pomoc_triggered()
{
    //Pomoc pomoc;
    //pomoc.setModal(true);
    //pomoc.exec();
    pomoc = new Pomoc(this);
    pomoc->show();
}
