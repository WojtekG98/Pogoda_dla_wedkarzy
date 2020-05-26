#include "glowneokno.h"
#include "ui_glowneokno.h"


GlowneOkno::GlowneOkno(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GlowneOkno)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager();
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));
    okresyochronne = new OkresyOchronne(this);
    QString okresy = "";
    int i = 0;
    while (okresyochronne->Okresy_ochronne_list.size() != 0)
    {
        if (okresyochronne->Okresy_ochronne_list.first()["desc"].toString() != "brak")
            okresy += okresyochronne->Okresy_ochronne_list.first()["name"].toString();
        i++;
        if (i%3 == 0)
            okresy += "\n";
        else
            okresy += ", ";
        okresyochronne->Okresy_ochronne_list.removeFirst();
    }
    ui->gatunki_chronione->setText(okresy);
    delete  okresyochronne;
    WarunkiDoPolowow.fill(0, 6);
    Temperatury.fill(0, 6);
    emit on_actionOdra_Wroc_aw_triggered();
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
        QString path = ":/ikony_openweather/ikony/pogoda.txt";//QCoreApplication::applicationDirPath() + QString("/pogoda.txt");
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly)){
            file.close();
        } else {
            QTextStream out(&file);
            out << jsonDoc.toJson(QJsonDocument::Indented);
            file.close();
        }
        this->PogodaDzis.daneZmienione(jsonDoc);
        ui->temperatura_srednia->setText(QString::number(PogodaDzis.Temperatura())+" °C");
        ui->temperatura_odczuwalna->setText(QString::number(PogodaDzis.TemperaturaOdczuwalna())+" °C");
        ui->temperatura_minimalna->setText(QString::number(PogodaDzis.TemperaturaMin())+" °C");
        ui->temperatura_maxymalna->setText(QString::number(PogodaDzis.TemperaturaMax())+" °C");
        ui->cisnienie->setText(QString::number(PogodaDzis.Cisnienie())+" hPa");
        ui->wilgotnosc_powietrza->setText(QString::number(PogodaDzis.Wilgotnosc())+" %");
        ui->kierunek_wiatru->setText(QString::number(PogodaDzis.KatWiatru())+" °");
        QString arr[8] = {"Pn.","Pn.-Wsch.","Wsch.", "Pd.-Wsch.", "Pd.", "Pd.-Zach.", "Zach.", "Pn.-Zach."};
        ui->kierunek_wiatru->setText(arr[(PogodaDzis.KatWiatru()/45)%8]);
        qDebug() << "Kierunek:" << PogodaDzis.KatWiatru() << round(double(PogodaDzis.KatWiatru())/45);
        ui->predkosc_wiatru->setText(QString::number(PogodaDzis.PredkoscWiatru()*3.6)+" km/h");
        QPixmap ikonaPogoda(PogodaDzis.IkonaPogody(1));
        ui->ikona_pogody_teraz->setPixmap(ikonaPogoda.scaled(200,200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else if (reply->url() ==QUrl(QString("http://api.openweathermap.org/data/2.5/forecast?id=")+Miasto+QString("&appid=")+APPID))
    {
        QString path = ":/ikony_openweather/ikony/prognoza.txt";//QCoreApplication::applicationDirPath() + QString("/prognoza.txt");
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly)){
            file.close();
        } else {
            QTextStream out(&file);
            out << jsonDoc.toJson(QJsonDocument::Indented);
            file.close();
        }
        Prognoza.prognozaZmieniona(jsonDoc);
        QVector<double> PrognozowaneTemperatury = Prognoza.Temperatury(),
                        PrognozowanePredkosciWiatrow = Prognoza.PredkosciWiatrow();

        QVector<unsigned int> PrognozowaneKierunkiWiatrow = Prognoza.KatyWiatrow(),
                              PrognozowaneCisnienia = Prognoza.Cisnienia();
        QVector<QPixmap> ikonyPogod;
        for (int i = 0; i < Prognoza.IkonyPogod(1).size(); i++){
            ikonyPogod.append(Prognoza.IkonyPogod(1)[i]);
            ikonyPogod[i] = ikonyPogod[i].scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        ui->temperatura_prognoza_1->setText(QString::number(PrognozowaneTemperatury[0])+" °C");
        ui->temperatura_prognoza_2->setText(QString::number(PrognozowaneTemperatury[1])+" °C");
        ui->temperatura_prognoza_3->setText(QString::number(PrognozowaneTemperatury[2])+" °C");
        ui->temperatura_prognoza_4->setText(QString::number(PrognozowaneTemperatury[3])+" °C");
        ui->temperatura_prognoza_5->setText(QString::number(PrognozowaneTemperatury[4])+" °C");
        ui->predkosc_wiatru_prognoza_1->setText(QString::number(PrognozowanePredkosciWiatrow[0]*3.6)+" km/h");
        ui->predkosc_wiatru_prognoza_2->setText(QString::number(PrognozowanePredkosciWiatrow[1]*3.6)+" km/h");
        ui->predkosc_wiatru_prognoza_3->setText(QString::number(PrognozowanePredkosciWiatrow[2]*3.6)+" km/h");
        ui->predkosc_wiatru_prognoza_4->setText(QString::number(PrognozowanePredkosciWiatrow[3]*3.6)+" km/h");
        ui->predkosc_wiatru_prognoza_5->setText(QString::number(PrognozowanePredkosciWiatrow[4]*3.6)+" km/h");
        ui->cisnienie_prognoza_1->setText(QString::number(PrognozowaneCisnienia[0]) + " hPa");
        ui->cisnienie_prognoza_2->setText(QString::number(PrognozowaneCisnienia[1]) + " hPa");
        ui->cisnienie_prognoza_3->setText(QString::number(PrognozowaneCisnienia[2]) + " hPa");
        ui->cisnienie_prognoza_4->setText(QString::number(PrognozowaneCisnienia[3]) + " hPa");
        ui->cisnienie_prognoza_5->setText(QString::number(PrognozowaneCisnienia[4]) + " hPa");
        ui->ikona_prognoza_1->setPixmap(ikonyPogod[0]);
        ui->ikona_prognoza_2->setPixmap(ikonyPogod[1]);
        ui->ikona_prognoza_3->setPixmap(ikonyPogod[2]);
        ui->ikona_prognoza_4->setPixmap(ikonyPogod[3]);
        ui->ikona_prognoza_5->setPixmap(ikonyPogod[4]);
        QPixmap *pixmap = new QPixmap(":/ikony_openweather/ikony/dir.png");
        QTransform transform[5];
        QTransform trans[5] = {transform[0].rotate(PrognozowaneKierunkiWiatrow[0]), transform[1].rotate(PrognozowaneKierunkiWiatrow[1]),
                               transform[2].rotate(PrognozowaneKierunkiWiatrow[2]), transform[3].rotate(PrognozowaneKierunkiWiatrow[3]),
                               transform[4].rotate(PrognozowaneKierunkiWiatrow[4])};
        QPixmap *transPixmap = new QPixmap(pixmap->transformed(trans[0]));
        ui->kierunek_wiatru_prognoza_1->setPixmap(transPixmap->scaled(20, 20,Qt::KeepAspectRatio, Qt::SmoothTransformation));
        *transPixmap = QPixmap(pixmap->transformed(trans[1]));
        ui->kierunek_wiatru_prognoza_2->setPixmap(transPixmap->scaled(20, 20,Qt::KeepAspectRatio, Qt::SmoothTransformation));
        *transPixmap = QPixmap(pixmap->transformed(trans[2]));
        ui->kierunek_wiatru_prognoza_3->setPixmap(transPixmap->scaled(20, 20,Qt::KeepAspectRatio, Qt::SmoothTransformation));
        *transPixmap = QPixmap(pixmap->transformed(trans[3]));
        ui->kierunek_wiatru_prognoza_4->setPixmap(transPixmap->scaled(20, 20,Qt::KeepAspectRatio, Qt::SmoothTransformation));
        *transPixmap = QPixmap(pixmap->transformed(trans[4]));
        ui->kierunek_wiatru_prognoza_5->setPixmap(transPixmap->scaled(20, 20,Qt::KeepAspectRatio, Qt::SmoothTransformation));
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
    Nazwa_Miasta = "Nysa Kłodzka w Bardzie";
    QPixmap mapa(":/ikony_openweather/ikony/Bardo.PNG");
    ui->mapa_lokalizacji->setPixmap(mapa.scaled(ui->mapa_lokalizacji->size(),Qt::KeepAspectRatio));
    emit on_action_odswiez_triggered();
}

void GlowneOkno::on_actionDunajec_Czch_w_triggered()
{
    Miasto = "773832";
    Nazwa_Miasta = "Dunajec - Czchów";
    QPixmap mapa(":/ikony_openweather/ikony/Czchów.PNG");
    ui->mapa_lokalizacji->setPixmap(mapa.scaled(ui->mapa_lokalizacji->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    emit on_action_odswiez_triggered();
}

/*!
 * \brief GlowneOkno::on_action_odswiez_triggered
 */
void GlowneOkno::on_action_odswiez_triggered()
{
    ui->nazwa_miasta->setText(Nazwa_Miasta);
    QDateTime aktualna = QDateTime::currentDateTime();
    ui->aktualna_godzina->setText(aktualna.toString("hh:mm"));
    ui->data->setText(aktualna.toString("dd.MM.yyyy"));
    QString aktualny_dzien_tyg = aktualna.toString("dddd");
    aktualny_dzien_tyg[0] = aktualny_dzien_tyg.at(0).toTitleCase();
    ui->dzien_tygodnia->setText(aktualny_dzien_tyg);
    ui->dzien_prognoza_1->setText(aktualna.addDays(1).toString("ddd"));
    ui->dzien_prognoza_2->setText(aktualna.addDays(2).toString("ddd"));
    ui->dzien_prognoza_3->setText(aktualna.addDays(3).toString("ddd"));
    ui->dzien_prognoza_4->setText(aktualna.addDays(4).toString("ddd"));
    ui->dzien_prognoza_5->setText(aktualna.addDays(5).toString("ddd"));
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
    UstawRybki();
}

void GlowneOkno::on_actionWy_wietl_triggered()
{
    okresyochronne = new OkresyOchronne(this);
    okresyochronne->show();
}

void GlowneOkno::UstawRybki()
{
    double tablica_wspolczynnikow[6] = {0, 0, 0, 0, 0, 0},
           lut[8] = {2, 2, 1, 1, 0, 1, 1, 2};
    QVector<double> tablica_temperatur;
    QVector<QString> tablica_ikon;
    QVector<unsigned int> tablica_kierunkow;

    tablica_temperatur.append(PogodaDzis.Temperatura());
    tablica_temperatur.append(Prognoza.Temperatury());
    tablica_ikon.append(PogodaDzis.IkonaPogody(1));
    tablica_ikon.append(Prognoza.IkonyPogod(1));
    tablica_kierunkow.append(PogodaDzis.KatWiatru());
    tablica_kierunkow.append(Prognoza.KatyWiatrow());
    for (int i = 0; i < 6; i++) {
        tablica_wspolczynnikow[i] = lut[(tablica_kierunkow[i]/45)%8];
        if (tablica_temperatur[i] > 15 && tablica_temperatur[i] < 25)
            tablica_wspolczynnikow[i] += 2;
        else if (tablica_temperatur[i] > 10 && tablica_temperatur[i] < 30)
            tablica_wspolczynnikow[i] += 1;
        if (tablica_ikon[i] != ":/ikony_qt/icons/weather-showers.png" && tablica_ikon[i] != ":/ikony_qt/icons/weather-storm.png")
            tablica_wspolczynnikow[i]++;
        Temperatury[i] = tablica_temperatur[i];
        WarunkiDoPolowow[i] = tablica_wspolczynnikow[i];
        UstawRybki(tablica_wspolczynnikow[i], i+1);
    }
}

void GlowneOkno::UstawRybki(int ilosc, int numer)
{
    QLabel *tablica_wskaznikow_label[30] = { ui->rybka1, ui->rybka2, ui->rybka3, ui->rybka4, ui->rybka5,
                                             ui->rybka_prognoza_1_1, ui->rybka_prognoza_1_2, ui->rybka_prognoza_1_3, ui->rybka_prognoza_1_4, ui->rybka_prognoza_1_5,
                                             ui->rybka_prognoza_2_1, ui->rybka_prognoza_2_2, ui->rybka_prognoza_2_3, ui->rybka_prognoza_2_4, ui->rybka_prognoza_2_5,
                                             ui->rybka_prognoza_3_1, ui->rybka_prognoza_3_2, ui->rybka_prognoza_3_3, ui->rybka_prognoza_3_4, ui->rybka_prognoza_3_5,
                                             ui->rybka_prognoza_4_1, ui->rybka_prognoza_4_2, ui->rybka_prognoza_4_3, ui->rybka_prognoza_4_4, ui->rybka_prognoza_4_5,
                                             ui->rybka_prognoza_5_1, ui->rybka_prognoza_5_2, ui->rybka_prognoza_5_3, ui->rybka_prognoza_5_4, ui->rybka_prognoza_5_5};
    int w = 50;
    int h = 50;
    QPixmap pelna_rybka(":/ikony_openweather/ikony/ryba_pelna.png"),
            pusta_rybka(":/ikony_openweather/ikony/ryba_pusta.png");

    if (numer == 1){
        w = 1.5*w;
        h = 1.5*h;
    }
    for (int i = (numer-1)*5; i < (numer-1)*5 + 5; i++) {
        if (i < ilosc + (numer-1)*5)
            tablica_wskaznikow_label[i]->setPixmap(pelna_rybka.scaled(w, h, Qt::KeepAspectRatio));
        else
            tablica_wskaznikow_label[i]->setPixmap(pusta_rybka.scaled(w, h, Qt::KeepAspectRatio));
    }
}

void GlowneOkno::on_actionOdra_Wroc_aw_triggered()
{
    Miasto = "3081368";
    Nazwa_Miasta = "Odra - Wrocław";
    QPixmap mapa(":/ikony_openweather/ikony/Wrocław.PNG");
    ui->mapa_lokalizacji->setPixmap(mapa.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    emit on_action_odswiez_triggered();
}

void GlowneOkno::on_actionWy_wietl_wykresy_triggered()
{
    wykresy = new Wykresy(this, WarunkiDoPolowow, Temperatury, Nazwa_Miasta);
    wykresy->show();
}
