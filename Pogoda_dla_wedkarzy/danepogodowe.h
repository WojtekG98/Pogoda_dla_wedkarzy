#ifndef DANEPOGODOWE_H
#define DANEPOGODOWE_H

#include <QObject>
#include <QtCore/QString>
#include <QtQml/QQmlListProperty>
#include <QJsonDocument>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QTime>
#define Kelvin 273.15

class DanePogodowe : public QObject
{
public:
    explicit DanePogodowe(QObject *parent = nullptr);
    double Temperatura() const;
    double TemperaturaOdczuwalna() const;
    double TemperaturaMax() const;
    double TemperaturaMin() const;
    double PredkoscWiatru() const;
    unsigned int Wilgotnosc() const;
    unsigned int Cisnienie() const;
    unsigned int KatWiatru() const;
    QTime CzasWschod() const;
    QTime CzasZachod() const;
    QString NazwaMiasta() const;
    QString OpisPogody() const;
    QString IkonaPogody() const;
    QString Wyswietl();
private:
    double feels_like;
    unsigned int humidity;
    unsigned int pressure;
    double temp;
    double temp_max;
    double temp_min;
    QTime sunrise;
    QTime sunset;
    unsigned int deg;
    double speed;
    QString name;
    QString description;
    QString icon;

signals:
    void daneZmienione(QJsonDocument dane);
};

#endif // DANEPOGODOWE_H
