#ifndef DANEPROGNOZA_H
#define DANEPROGNOZA_H

#include <QObject>
#include <QJsonDocument>
#include <QtCore/QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#define Kelvin 273.15

class DanePrognoza : public QObject
{
    Q_OBJECT
public:
    explicit DanePrognoza(QObject *parent = nullptr);
    double * Temperatura(){
        return this->temp;
    }
    double * PredkoscWiatru(){
        return this->speed;
    }
    unsigned int * KatWiatru(){
        return this->deg;
    }
    unsigned int * Cisnienie(){
        return this->pressure;
    }
    QString IkonaPogody_1(uint8_t flag){
        return StringToIcon(this->icon[0], flag);
    }
    QString IkonaPogody_2(uint8_t flag){
        return StringToIcon(this->icon[1], flag);
    }
    QString IkonaPogody_3(uint8_t flag){
        return StringToIcon(this->icon[2], flag);;
    }
    QString IkonaPogody_4(uint8_t flag){
        return StringToIcon(this->icon[3], flag);
    }
    QString IkonaPogody_5(uint8_t flag){
        return StringToIcon(this->icon[4], flag);
    }
    QString StringToIcon(QString icon_txt, uint8_t flag);
    void prognozaZmieniona(QJsonDocument dane);
private:
    double temp[5];
    double speed[5];
    unsigned int deg[5];
    unsigned int pressure[5];
    QString icon[5];

signals:
};

#endif // DANEPROGNOZA_H
