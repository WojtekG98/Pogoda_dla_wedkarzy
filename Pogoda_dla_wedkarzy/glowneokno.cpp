#include "glowneokno.h"
#include "ui_glowneokno.h"
#include "pomoc.h"
#include <QtNetwork>
#include <QJsonDocument>

GlowneOkno::GlowneOkno(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GlowneOkno)
{
    ui->setupUi(this);
    ui->label->setText(this->Miasto);
    ui->textEdit->setText("Brak");
    ui->textEdit->setReadOnly(true);
    manager = new QNetworkAccessManager();
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
           this, SLOT(managerFinished(QNetworkReply*)));
    request.setUrl(QUrl(QString("http://api.openweathermap.org/data/2.5/weather?id=")+Miasto+QString("&appid=")+APPID));
    manager->get(request);
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
    //ui->textEdit->setText(jsonDoc.toJson(QJsonDocument::Indented));
    ui->textEdit->setText(this->PogodaDzis.Wyswietl());
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
    manager->get(request);
    ui->label->setText(this->Miasto);
    QPixmap ikonaPogoda(":/new/prefix1/icons/weather-fog.png");
    ui->label_2->setPixmap(ikonaPogoda);
    ui->label_2->setScaledContents(true);
    //ui->label_2->setMask(ikonaPogoda.mask());
}
