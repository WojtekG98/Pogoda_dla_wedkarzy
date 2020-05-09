#include "glowneokno.h"
#include "ui_glowneokno.h"


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
    loop.exec();
    request.setUrl(QUrl(QString("http://api.openweathermap.org/data/2.5/forecast?id=")+Miasto+QString("&appid=")+APPID));
    QNetworkReply *netReply2 = manager->get(request);
    QEventLoop loop2;
    connect(netReply2, SIGNAL(finished()), &loop2, SLOT(quit()));
    loop2.exec();
    ui->nazwa_miasta->setText("Wrocław");
    QString ikonatekst = PogodaDzis.IkonaPogody(1);
    QPixmap ikonaPogoda(ikonatekst),
            mapa(":/ikony_openweather/ikony/Bardo.PNG");
    int w = ui->mapa_lokalizacji->width(),
            h = ui->mapa_lokalizacji->height();
    ui->ikona_pogody_teraz->setPixmap(ikonaPogoda.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->mapa_lokalizacji->setPixmap(mapa.scaled(w,h,Qt::KeepAspectRatio));
    w = ui->rybka1->width();
    h = ui->rybka1->height();
    QPixmap rybka(":/ikony_openweather/ikony/ryba_pelna.png");
    ui->rybka1->setPixmap(rybka.scaled(w,h,Qt::KeepAspectRatio));
    ui->rybka2->setPixmap(rybka.scaled(w,h,Qt::KeepAspectRatio));
    ui->rybka3->setPixmap(rybka.scaled(w,h,Qt::KeepAspectRatio));
    ui->rybka4->setPixmap(rybka.scaled(w,h,Qt::KeepAspectRatio));
    ui->rybka5->setPixmap(rybka.scaled(w,h,Qt::KeepAspectRatio));

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

    if (reply->url() == QUrl(QString("http://api.openweathermap.org/data/2.5/weather?id=")+Miasto+QString("&appid=")+APPID))
    {
        QString path = QCoreApplication::applicationDirPath() + QString("/pogoda.txt");
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly)){
            file.close();
        } else {
            QTextStream out(&file);
            out << jsonDoc.toJson(QJsonDocument::Indented);
            file.close();
        }
        this->PogodaDzis.daneZmienione(jsonDoc);
        ui->temperatura_srednia->setText(QString::number(this->PogodaDzis.Temperatura())+" °C");
        ui->temperatura_odczuwalna->setText(QString::number(this->PogodaDzis.TemperaturaOdczuwalna())+" °C");
        ui->temperatura_minimalna->setText(QString::number(this->PogodaDzis.TemperaturaMin())+" °C");
        ui->temperatura_maxymalna->setText(QString::number(this->PogodaDzis.TemperaturaMax())+" °C");
        ui->cisnienie->setText(QString::number(this->PogodaDzis.Cisnienie())+" hPa");
        ui->wilgotnosc_powietrza->setText(QString::number(this->PogodaDzis.Wilgotnosc())+" %");
        ui->kierunek_wiatru->setText(QString::number(this->PogodaDzis.KatWiatru())+" °");
        ui->predkosc_wiatru->setText(QString::number(this->PogodaDzis.PredkoscWiatru())+" km/h");
        QPixmap ikonaPogoda(PogodaDzis.IkonaPogody(1));
        ui->ikona_pogody_teraz->setPixmap(ikonaPogoda.scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else if (reply->url() ==QUrl(QString("http://api.openweathermap.org/data/2.5/forecast?id=")+Miasto+QString("&appid=")+APPID))
    {
        QString path = QCoreApplication::applicationDirPath() + QString("/prognoza.txt");
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly)){
            file.close();
        } else {
            QTextStream out(&file);
            out << jsonDoc.toJson(QJsonDocument::Indented);
            file.close();
        }
        this->Prognoza.prognozaZmieniona(jsonDoc);
        double *temperatura = this->Prognoza.Temperatura();
        double *predkosc = this->Prognoza.PredkoscWiatru();
        unsigned int *katwiatru = this->Prognoza.KatWiatru();
        unsigned int *cisnienie = this->Prognoza.Cisnienie();
        ui->temperatura_prognoza_1->setText(QString::number(temperatura[0])+" °C");
        ui->temperatura_prognoza_2->setText(QString::number(temperatura[1])+" °C");
        ui->temperatura_prognoza_3->setText(QString::number(temperatura[2])+" °C");
        ui->temperatura_prognoza_4->setText(QString::number(temperatura[3])+" °C");
        ui->temperatura_prognoza_5->setText(QString::number(temperatura[4])+" °C");
        ui->predkosc_wiatru_prognoza_1->setText(QString::number(predkosc[0])+" km/h");
        ui->predkosc_wiatru_prognoza_2->setText(QString::number(predkosc[1])+" km/h");
        ui->predkosc_wiatru_prognoza_3->setText(QString::number(predkosc[2])+" km/h");
        ui->predkosc_wiatru_prognoza_4->setText(QString::number(predkosc[3])+" km/h");
        ui->predkosc_wiatru_prognoza_5->setText(QString::number(predkosc[4])+" km/h");
        ui->cisnienie_prognoza_1->setText(QString::number(cisnienie[0]) + " hPa");
        ui->cisnienie_prognoza_2->setText(QString::number(cisnienie[1]) + " hPa");
        ui->cisnienie_prognoza_3->setText(QString::number(cisnienie[2]) + " hPa");
        ui->cisnienie_prognoza_4->setText(QString::number(cisnienie[3]) + " hPa");
        ui->cisnienie_prognoza_5->setText(QString::number(cisnienie[4]) + " hPa");
        QPixmap ikonaPogoda(this->Prognoza.IkonaPogody_1(1));
        int h = 100;//ui->ikona_prognoza_1->height();
        ui->ikona_prognoza_1->setPixmap(ikonaPogoda.scaled(h,h,Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ikonaPogoda = this->Prognoza.IkonaPogody_2(1);
        ui->ikona_prognoza_2->setPixmap(ikonaPogoda.scaled(h,h,Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ikonaPogoda = this->Prognoza.IkonaPogody_3(1);
        ui->ikona_prognoza_3->setPixmap(ikonaPogoda.scaled(h,h,Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ikonaPogoda = this->Prognoza.IkonaPogody_4(1);
        ui->ikona_prognoza_4->setPixmap(ikonaPogoda.scaled(h,h,Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ikonaPogoda = this->Prognoza.IkonaPogody_5(1);
        ui->ikona_prognoza_5->setPixmap(ikonaPogoda.scaled(h,h,Qt::KeepAspectRatio, Qt::SmoothTransformation));
        int wa = ui->kierunek_wiatru_prognoza_1->width(),
                ha = ui->kierunek_wiatru_prognoza_1->height();
        QPixmap *pixmap = new QPixmap(":/ikony_openweather/ikony/dir.png");
        QTransform transform[5];
        QTransform trans[5] = {transform[0].rotate(katwiatru[0]), transform[1].rotate(katwiatru[1]), transform[2].rotate(katwiatru[2]), transform[3].rotate(katwiatru[3]), transform[4].rotate(katwiatru[4])};
        QPixmap *transPixmap = new QPixmap(pixmap->transformed(trans[0]));
        ui->kierunek_wiatru_prognoza_1->setPixmap(transPixmap->scaled(wa,ha,Qt::KeepAspectRatio, Qt::SmoothTransformation));
        *transPixmap = QPixmap(pixmap->transformed(trans[1]));
        ui->kierunek_wiatru_prognoza_2->setPixmap(transPixmap->scaled(wa,ha,Qt::KeepAspectRatio, Qt::SmoothTransformation));
        *transPixmap = QPixmap(pixmap->transformed(trans[2]));
        ui->kierunek_wiatru_prognoza_3->setPixmap(transPixmap->scaled(wa,ha,Qt::KeepAspectRatio, Qt::SmoothTransformation));
        *transPixmap = QPixmap(pixmap->transformed(trans[3]));
        ui->kierunek_wiatru_prognoza_4->setPixmap(transPixmap->scaled(wa,ha,Qt::KeepAspectRatio, Qt::SmoothTransformation));
        *transPixmap = QPixmap(pixmap->transformed(trans[4]));
        ui->kierunek_wiatru_prognoza_5->setPixmap(transPixmap->scaled(wa,ha,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
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
    request.setUrl(QUrl(QString("http://api.openweathermap.org/data/2.5/forecast?id=")+Miasto+QString("&appid=")+APPID));
    QNetworkReply *netReply2 = manager->get(request);
    QEventLoop loop2;
    connect(netReply2, SIGNAL(finished()), &loop2, SLOT(quit()));
    loop2.exec();
    ui->nazwa_miasta->setText("Nysa Kłodzka w Bardzie");
    QPixmap mapa(":/ikony_openweather/ikony/Bardo.PNG");
    ui->mapa_lokalizacji->setPixmap(mapa.scaled(100,100,Qt::KeepAspectRatio));
}

void GlowneOkno::on_actionDunajec_Czch_w_triggered()
{
    this->Miasto = "773832";
    request.setUrl(QUrl(QString("http://api.openweathermap.org/data/2.5/weather?id=")+Miasto+QString("&appid=")+APPID));
    QNetworkReply *netReply = manager->get(request);
    QEventLoop loop;
    connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    request.setUrl(QUrl(QString("http://api.openweathermap.org/data/2.5/forecast?id=")+Miasto+QString("&appid=")+APPID));
    QNetworkReply *netReply2 = manager->get(request);
    QEventLoop loop2;
    connect(netReply2, SIGNAL(finished()), &loop2, SLOT(quit()));
    loop2.exec();
    ui->nazwa_miasta->setText("Dunajec - Czhów");
    QPixmap mapa(":/ikony_openweather/ikony/czchow.png");
    ui->mapa_lokalizacji->setPixmap(mapa.scaled(100,100,Qt::KeepAspectRatio));
}

void GlowneOkno::on_action_odswiez_triggered()
{
    QDateTime aktualna = QDateTime::currentDateTime();
    ui->aktualna_godzina->setText(aktualna.toString("hh:mm"));
    ui->data->setText(aktualna.toString("dd.MM.yyyy"));
    request.setUrl(QUrl(QString("http://api.openweathermap.org/data/2.5/weather?id=")+Miasto+QString("&appid=")+APPID));
    QNetworkReply *netReply = manager->get(request);
    QEventLoop loop;
    connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    request.setUrl(QUrl(QString("http://api.openweathermap.org/data/2.5/forecast?id=")+Miasto+QString("&appid=")+APPID));
    QNetworkReply *netReply2 = manager->get(request);
    QEventLoop loop2;
    connect(netReply2, SIGNAL(finished()), &loop2, SLOT(quit()));
    loop2.exec();
}

void GlowneOkno::on_actionWy_wietl_triggered()
{
    okresyochronne = new OkresyOchronne(this);
    okresyochronne->show();
}
