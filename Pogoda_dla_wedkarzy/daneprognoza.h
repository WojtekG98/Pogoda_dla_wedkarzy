#ifndef DANEPROGNOZA_H
#define DANEPROGNOZA_H

#include <QObject>
#include <QJsonDocument>
#include <QtCore/QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include <QDebug>
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
     * \brief Prognozowane temperatury
     * \return Wektor prognozowanych temperatur na 5 kolejnych dni w stopniach celsjusza.
     */
    QVector<double> Temperatury() const{
        return temp;
    }
    /*!
     * \brief Prognozowane prędkości wiatrów
     * \return Wektor prognozowanych prędkości wiatrów na 5 kolejnych dni w m/s.
     */
    QVector<double> PredkosciWiatrow() const{
        return speed;
    }
    /*!
     * \brief Prognozowane kierunki wiatrów
     * \return Wektor prognozowanych meteorologicznych kierunków wiatrów na 5 kolejnych dni w stopniach.
     */
    QVector<unsigned int> KatyWiatrow() const{
        return deg;
    }
    /*!
     * \brief Prognozowane ciśnienia
     * \return Wektor prognozowanych ciśnień na 5 kolejnych dni w hPa.
     */
    QVector<unsigned int> Cisnienia() const{
        return pressure;
    }
    /*!
     * \brief Prognozowane id ikon pogód
     * \param flaga za pomocą której wybieramy typ ikon - 0 lub 1
     * \return Zwraca wektor ścieżek do prognozowanych ikon
     */
    QVector<QString> IkonyPogod(unsigned int flag){
        QVector<QString> sciezki;
        for (int i = 0; i < icon.size(); i++)
            sciezki.append(StringToIcon(icon[i], flag));
        return sciezki;
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
    /*!
     * \brief Wektor prognozwanych temperatur w stopniach celsjusza
     */
    QVector<double> temp;
    /*!
     * \brief Wektor prognozowanych prędkości wiatrów w m/s
     */
    QVector<double> speed;
    /*!
     * \brief Wektor prognozowanych meteorologicznych kierunków wiatrów w stopniach
     */
    QVector<unsigned int> deg;
    /*!
     * \brief Wektor prognozowanych cisnien w hPa
     */
    QVector<unsigned int> pressure;
    /*!
     * \brief Wektor prognozowanych id ikon pogodowych
     */
    QVector<QString> icon;
};

#endif // DANEPROGNOZA_H
