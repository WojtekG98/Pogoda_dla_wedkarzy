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

/*!
 * \brief Klasa DanePogodowe
 * Klasa zawiera w sobie dane o aktualnej pogodzie, oraz funkcję przetwarzająca
 * odpowiedź WeatherAPI.
 */
class DanePogodowe : public QObject
{
public:
    /*!
     * \brief Konstruktor
     * \param parent
     */
    explicit DanePogodowe(QObject *parent = nullptr);
    /*!
     * \brief Temperatura
     * \return Temperatura w stopniach celsjusza.
     */
    double Temperatura() const;
    /*!
     * \brief Odczuwalna temperatura
     * \return Odczuwalna temperatura w stopniach celsjusza.
     */
    double TemperaturaOdczuwalna() const;
    /*!
     * \brief Temperatura maksymalna
     * \return Maksymalna zarejestrowana w danym obszarze (dla dużych miast) temperatura w stopniach celsjusza.
     */
    double TemperaturaMax() const;
    /*!
     * \brief Temperatura minimalna
     * \return Minimalna zarejestrowana w danym obszarze (dla dużych miast) temperatura w stopniach celsjusza.
     */
    double TemperaturaMin() const;
    /*!
     * \brief Predkosc wiatru
     * \return Predkosc wiatru w m/s.
     */
    double PredkoscWiatru() const;
    /*!
     * \brief Wilgotnosc
     * \return Wilgotnosc powietrza w %.
     */
    unsigned int Wilgotnosc() const;
    /*!
     * \brief Cisnienie
     * \return Cisnienie w hPa.
     */
    unsigned int Cisnienie() const;
    /*!
     * \brief Kierunek wiatru
     * \return Meteorologiczny kąt wiatru w stopniach.
     */
    unsigned int KatWiatru() const;
    /*!
     * \brief Czas wschod słońca
     * \return Czas POSIX wschodu słońca z klasy.
     */
    QTime CzasWschod() const;
    /*!
     * \brief Czas zachodu słońca
     * \return Czas POSIX zachodu słońca z klasy.
     */
    QTime CzasZachod() const;
    /*!
     * \brief Nazwa miasta
     * \return Nazwe miasta z klasy.
     */
    QString NazwaMiasta() const;
    /*!
     * \brief Opis pogody
     * \return Opis pogody jako QString z klasy.
     */
    QString OpisPogody() const;
    /*!
     * \brief Określ ścieżke ikony zawartej w klasie
     * \param flag  0 lub 1, 0 - ikony dostarczone przez OpenWeather, 1 - ikony z http://tango.freedesktop.org/Tango_Icon_Library oraz http://darkobra.deviantart.com/art/Tango-Weather-Icon-Pack-98024429
     * \return Ścieżkę ikony jako QString w zależności od parametru flag.
     */
    QString IkonaPogody(uint8_t flag) const;
    /*!
     * \brief Wyswietl dane z klasy
     * \return Dane zawarte w swojej klasie w postaci tekstowej.
     */
    QString Wyswietl();
private:
    /*!
     * \brief Aktualna temperatura odczuwalna, stopnie celsjusza
     */
    double feels_like;
    /*!
     * \brief Aktualna wilgotnosc, %
     */
    unsigned int humidity;
    /*!
     * \brief Aktualne ciśnienie, hPa
     */
    unsigned int pressure;
    /*!
     * \brief Aktualna temperatura, stopnie celsjusza
     */
    double temp;
    /*!
     * \brief Maksymalna zarejestrowana temperatura, stopnie celsjusza
     */
    double temp_max;
    /*!
     * \brief Minimalna zarejestrowana temperatura, stopnie celsjusza
     */
    double temp_min;
    /*!
     * \brief Czas wschodu słońca, czas POSIX
     */
    QTime sunrise;
    /*!
     * \brief Czas zachodu słońca, czas POSIX
     */
    QTime sunset;
    /*!
     * \brief Kierunek wiatru (meteorologiczny), stopnie
     */
    unsigned int deg;
    /*!
     * \brief Predkosc wiatru, m/s
     */
    double speed;
    /*!
     * \brief Nazwa miasta
     */
    QString name;
    /*!
     * \brief Opis pogody
     */
    QString description;
    /*!
     * \brief id ikony pogody
     */
    QString icon;

signals:
    /*!
     * \brief daneZmienione
     * \param dane
     * Funkcja wpisuje dane zawarte w parametrze "dane" do swojej struktury danych.
     */
    void daneZmienione(QJsonDocument dane);
};

#endif // DANEPOGODOWE_H
