#ifndef DANEPROGNOZA_H
#define DANEPROGNOZA_H

#include <QObject>
#include <QJsonDocument>
#include <QtCore/QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#define Kelvin 273.15

/*!
 * \brief Klasa DanePrognoza
 * Klasa zawiera w sobie prognozowane dane pogodowe na 5 kolejnych dni oraz funkcję przetwarzającą odpowiedź z ForecastAPI.
 */
class DanePrognoza : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor
     * \param parent
     */
    explicit DanePrognoza(QObject *parent = nullptr);
    /*!
     * \brief Prognozowana temperatura
     * \return Wskaźnik na tablicę z prognozowaną temperaturą na 5 kolejnych dni w stopniach celsjusza.
     */
    double * Temperatura(){
        return this->temp;
    }
    /*!
     * \brief Prognozowana prędkość wiatru
     * \return Wskaźnik na tablicę z prognozowaną prędkościa wiatru na 5 kolejnych dni w m/s.
     */
    double * PredkoscWiatru(){
        return this->speed;
    }
    /*!
     * \brief Prognozowany kierunek wiatru
     * \return Wskaźnik na tablicę z prognozowanym meteorologicznym kierunkiem wiatru na 5 kolejnych dni w stopniach.
     */
    unsigned int * KatWiatru(){
        return this->deg;
    }
    /*!
     * \brief Prognozowane ciśnienie
     * \return Wskaźnik na tablicę z prognozowanym ciśnieniem na 5 kolejnych dni w hPa.
     */
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
    /*!
     * \brief Przekształca id ikony w ścieżkę do ikony
     * \param icon_txt
     * \param flag
     * \return W zależności od parametru flag zwraca ścieżkę do ikony określonej parametrem icon_txt.
     */
    QString StringToIcon(QString icon_txt, uint8_t flag);
    /*!
     * \brief prognozaZmieniona
     * \param dane
     * Funkcja wpisuje dane zawarte w parametrze "dane" do swojej struktury danych.
     */
    void prognozaZmieniona(QJsonDocument dane);
private:
    double temp[5]; /*!< Tablica prognozwanych temperatur w stopniach celsjusza */
    double speed[5]; /*!< Tablica prognozowanych prędkości wiatrów w m/s */
    unsigned int deg[5]; /*!< Tablica prognozowanych kierunków wiatrów w stopniach */
    unsigned int pressure[5]; /*!< Tablica prognozowanych ciśnień w hPa */
    QString icon[5]; /*!< Tablica prognozowanych id ikon pogodowych */
};

#endif // DANEPROGNOZA_H
