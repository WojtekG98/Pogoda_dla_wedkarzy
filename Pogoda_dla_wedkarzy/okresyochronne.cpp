#include "okresyochronne.h"
#include "ui_okresyochronne.h"

OkresyOchronne::OkresyOchronne(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OkresyOchronne)
{
    ui->setupUi(this);
    QString data = "";
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
    ui->Bolen_text->setHtml("<p style=\"text-align: center; font-size:16px\">Boleń:"
                            "<p style=\"text-align: center\">od 1 stycznia"
                            "<p style=\"text-align: center\">do 30 kwietnia");
    ui->Brzana_text->setHtml("<p style=\"text-align: center; font-size:16px\">Brzana:"
                            "<p style=\"text-align: center\">od 1 stycznia"
                            "<p style=\"text-align: center\">do 30 czerwca");
    ui->Certa_text->setHtml("<p style=\"text-align: center; font-size:16px\">Certa:"
                            "<p style=\"text-align: center\">W rzece Wiśle od zapory we Włocławku do jej ujścia:"
                            "<p style=\"text-align: center\">od 1 września do 30 listopada"
                            "<p style=\"text-align: center\">W rzece Wiśle powyżej zapory we Włocławku i w pozostałych rzekach:"
                            "<p style=\"text-align: center\">od 1 stycznia do 30 czerwca.");
    //ui->Bolen_text->setText("Boleń:\n od 1 stycznia\n do 30 czerwca");
    //ui->Bolen_text->setAlignment(Qt::AlignCenter);
    //ui->OkresyOchronneTekst->setText(data);
}

OkresyOchronne::~OkresyOchronne()
{
    delete ui;
}
