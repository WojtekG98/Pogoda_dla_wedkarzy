#ifndef OKRESYOCHRONNE_H
#define OKRESYOCHRONNE_H

#include <QDialog>
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class OkresyOchronne;
}
/*!
 * \brief klasa OkresyOchronne
 * Klasa zawiera w sobie informacje na temat okresów ochronnych ryb oraz implementuje okno okresy ochronne.
 */
class OkresyOchronne : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor
     * \param parent
     */
    explicit OkresyOchronne(QWidget *parent = nullptr);
    ~OkresyOchronne();

private:
    Ui::OkresyOchronne *ui;
public:
    QJsonArray Okresy_ochronne_list;
    QString desc;
};

#endif // OKRESYOCHRONNE_H
