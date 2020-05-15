#include "okresyochronne.h"
#include "ui_okresyochronne.h"

OkresyOchronne::OkresyOchronne(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OkresyOchronne)
{
    ui->setupUi(this);
    QString data = "";
    ui->OkresyOchronneTekst->setReadOnly(true);
    ui->OkresyOchronneTekst->setText("Jest git");
    QFile file(":/ikony_openweather/ikony/okresy_ochronne.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        file.close();
    }
    else
    {
        data = file.readAll();
        file.close();
    }
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
    data = "";
    QJsonObject jo = jsonDoc.object();
    QJsonArray list = jo["list"].toArray();
    desc = jo["decription"].toString();
    data += jo["description"].toString() + "\n\n";
    while (list.size() != 0)
    {
        data += list.first()["name"].toString() + ": " + list.first()["period"].toString() + "\n";
        if (list.first()["period"] != "brak")
        {
            QJsonObject temp = list.first().toObject();
            this->Okresy_ochronne_list.append(temp);
        }
        list.removeFirst();
    }
    ui->OkresyOchronneTekst->setText(data);
}

OkresyOchronne::~OkresyOchronne()
{
    delete ui;
}
