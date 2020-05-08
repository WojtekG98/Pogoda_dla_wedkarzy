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
    double Temperatura_1() const{
        return this->temp[0];
    }
    double Temperatura_2() const{
        return this->temp[1];
    }
    double Temperatura_3() const{
        return this->temp[2];
    }
    double Temperatura_4() const{
        return this->temp[3];
    }
    double Temperatura_5() const{
        return this->temp[4];
    }
    double PredkoscWiatru_1() const{
        return this->speed[0];
    }
    double PredkoscWiatru_2() const{
        return this->speed[1];
    }
    double PredkoscWiatru_3() const{
        return this->speed[2];
    }
    double PredkoscWiatru_4() const{
        return this->speed[3];
    }
    double PredkoscWiatru_5() const{
        return this->speed[4];
    }
    unsigned int KatWiatru_1() const{
        return this->deg[0];
    }
    unsigned int KatWiatru_2() const{
        return this->deg[1];
    }
    unsigned int KatWiatru_3() const{
        return this->deg[2];
    }
    unsigned int KatWiatru_4() const{
        return this->deg[3];
    }
    unsigned int KatWiatru_5() const{
        return this->deg[4];
    }
    unsigned int Cisnienie_1() const{
        return this->pressure[0];
    }
    unsigned int Cisnienie_2() const{
        return this->pressure[1];
    }
    unsigned int Cisnienie_3() const{
        return this->pressure[2];
    }
    unsigned int Cisnienie_4() const{
        return this->pressure[3];
    }
    unsigned int Cisnienie_5() const{
        return this->pressure[4];
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
