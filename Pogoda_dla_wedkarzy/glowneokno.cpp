#include "glowneokno.h"
#include "ui_glowneokno.h"
#include "pomoc.h"
#include <QtNetwork>
#include <QJsonDocument>
#include <QDateTime>

GlowneOkno::GlowneOkno(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GlowneOkno)
{
    QDateTime aktualna = QDateTime::currentDateTime();
    QString aktualna_godz = aktualna.toString("hh:mm"),
            aktualna_data = aktualna.toString("dd.MM.yyyy"),
            aktualny_dzien_tyg = aktualna.toString("dddd");
    aktualny_dzien_tyg[0] = aktualny_dzien_tyg.at(0).toTitleCase();
    ui->setupUi(this);
    ui->nazwa_miasta->setText(this->Miasto);
    ui->aktualna_godzina->setText(aktualna_godz);
    ui->data->setText(aktualna_data);
    ui->dzien_tygodnia->setText(aktualny_dzien_tyg);
    ui->dzien_prognoza_1->setText(aktualna.addDays(1).toString("ddd"));
    ui->dzien_prognoza_2->setText(aktualna.addDays(2).toString("ddd"));
    ui->dzien_prognoza_3->setText(aktualna.addDays(3).toString("ddd"));
    ui->dzien_prognoza_4->setText(aktualna.addDays(4).toString("ddd"));
    ui->dzien_prognoza_5->setText(aktualna.addDays(5).toString("ddd"));
    manager = new QNetworkAccessManager();
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));
    request.setUrl(QUrl(QString("http://api.openweathermap.org/data/2.5/weather?id=")+Miasto+QString("&appid=")+APPID));
    QNetworkReply *netReply = manager->get(request);
    QEventLoop loop;
    connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));
    ui->statusbar->showMessage("Łączenie z OpenWeather...",100);
    loop.exec();
    ui->statusbar->showMessage("Połączono!",10);
    ui->nazwa_miasta->setText("Wrocław");
    QString ikonatekst = PogodaDzis.IkonaPogody();
    QPixmap ikonaPogoda(ikonatekst),
            mapa(":/ikony_openweather/ikony/Bardo.PNG");
    ui->ikona_pogody_teraz->setPixmap(ikonaPogoda.scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    //ui->ikona_pogody_teraz->setPixmap(ikonaPogoda.scaled(100,100,Qt::IgnoreAspectRatio));
    ui->mapa_lokalizacji->setPixmap(mapa.scaled(100,100,Qt::IgnoreAspectRatio));
    ui->ikona_pogody_teraz->setAutoFillBackground(true);
    QPalette pal = ui->ikona_pogody_teraz->palette();
    pal.setColor(QPalette::Window, QColor(Qt::white));
    ui->ikona_pogody_teraz->setPalette(pal);
}

GlowneOkno::~GlowneOkno()
{
    delete ui;
    delete manager;
}

void GlowneOkno::managerFinished(QNetworkReply *reply){

    if (reply->error())
    {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(answer.toUtf8());

    QString path= QCoreApplication::applicationDirPath() + QString("/pogoda.txt");
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly)){
        file.close();
    } else {
        QTextStream out(&file);
        out << jsonDoc.toJson(QJsonDocument::Indented);
        file.close();
    }
    //qDebug() << jsonDoc.toJson(QJsonDocument::Indented);
    this->PogodaDzis.daneZmienione(jsonDoc);
    //ui->tmp_text->setText(this->PogodaDzis.Wyswietl());
    ui->temperatura_srednia->setText(QString::number(this->PogodaDzis.Temperatura())+" °C");
    ui->temperatura_odczuwalna->setText(QString::number(this->PogodaDzis.TemperaturaOdczuwalna())+" °C");
    ui->temperatura_minimalna->setText(QString::number(this->PogodaDzis.TemperaturaMin())+" °C");
    ui->temperatura_maxymalna->setText(QString::number(this->PogodaDzis.TemperaturaMax())+" °C");
    ui->cisnienie->setText(QString::number(this->PogodaDzis.Cisnienie())+" hPa");
    ui->wilgotnosc_powietrza->setText(QString::number(this->PogodaDzis.Wilgotnosc())+" %");
    ui->kierunek_wiatru->setText(QString::number(this->PogodaDzis.KatWiatru())+" °");
    ui->predkosc_wiatru->setText(QString::number(this->PogodaDzis.PredkoscWiatru())+" km/h");
}

void GlowneOkno::on_actionWy_wietl_pomoc_triggered()
{
    pomoc = new Pomoc(this);
    pomoc->show();
}

void GlowneOkno::on_actionNysa_K_odzka_w_Bardzie_triggered()
{
    this->Miasto="3103847";
    request.setUrl(QUrl(QString("http://api.openweathermap.org/data/2.5/weather?id=")+Miasto+QString("&appid=")+APPID));
    QNetworkReply *netReply = manager->get(request);
    QEventLoop loop;
    connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    ui->nazwa_miasta->setText("Nysa Kłodzka w Bardzie");
    QString ikonatekst = PogodaDzis.IkonaPogody();
    //ui->statusbar->showMessage(ikonatekst);
    QPixmap ikonaPogoda(ikonatekst);
    ui->ikona_pogody_teraz->setPixmap(ikonaPogoda.scaled(100,100,Qt::IgnoreAspectRatio));
    ui->ikona_pogody_teraz->setAutoFillBackground(true);
    QPalette pal = ui->ikona_pogody_teraz->palette();
    pal.setColor(QPalette::Window, QColor(Qt::white));
    ui->ikona_pogody_teraz->setPalette(pal);
}
