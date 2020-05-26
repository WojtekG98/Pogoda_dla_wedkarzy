#ifndef GLOWNEOKNO_H
#define GLOWNEOKNO_H

#include <QMainWindow>
#include <QtNetwork>
#include <QDateTime>
#include "pomoc.h"
#include "danepogodowe.h"
#include "daneprognoza.h"
#include "okresyochronne.h"
#include "wykresy.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GlowneOkno; }
QT_END_NAMESPACE
/*!
 * \brief Klasa GlowneOkno
 * Klasa dziedzicząca QMainWindow stanowiąca główne okno aplikacji.
 */
class GlowneOkno : public QMainWindow
{
    Q_OBJECT

public:
    GlowneOkno(QWidget *parent = nullptr);
    ~GlowneOkno();

private slots:
    /*!
     * \brief managerFinished
     * \param reply
     */
    void managerFinished(QNetworkReply *reply);
    /*!
     * \brief on_actionWy_wietl_pomoc_triggered
     */
    void on_actionWy_wietl_pomoc_triggered();
    /*!
     * \brief on_actionNysa_K_odzka_w_Bardzie_triggered
     */
    void on_actionNysa_K_odzka_w_Bardzie_triggered();
    /*!
     * \brief on_actionDunajec_Czch_w_triggered
     */
    void on_actionDunajec_Czch_w_triggered();
    /*!
     * \brief on_action_odśwież_triggered
     */
    void on_action_odswiez_triggered();
    /*!
     * \brief on_action_Wyświetl_triggered
     */
    void on_actionWy_wietl_triggered();
    void on_actionOdra_Wroc_aw_triggered();

    void on_actionWy_wietl_wykresy_triggered();

private:
    Ui::GlowneOkno *ui;
    Pomoc *pomoc;
    OkresyOchronne *okresyochronne;
    Wykresy *wykresy;
    DanePogodowe PogodaDzis;
    DanePrognoza Prognoza;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QVector<int> WarunkiDoPolowow;
    QVector<int> Temperatury;
    QString APPID = "f2e1064de8457c7d5680e0e1925d5f86";
    QString Miasto = "3081368";
    QString Nazwa_Miasta = "Wrocław - Odra";
    /*!
     * \brief Funkcja ustawiająca rybki
     * Funkcja wyliczająca na podstawie aktualnych i prognozowanych danych pogodowych warunki do połowu ryb i ustawiająca rybki.
     */
    void UstawRybki();
    /*!
     * \brief Funkcja ustawiająca ilosc rybek kolorowych,a 5-ilosc rybek pustych
     * \param ilosc - ilość kolorowych rybek
     * \param numer - numer label'a, którego dotyczy wywołanie
     */
    void UstawRybki(int ilosc, int numer);
};
#endif // GLOWNEOKNO_H
