#ifndef WYKRESY_H
#define WYKRESY_H

#include <QDialog>
//#include <QtCharts>

namespace Ui {
class Wykresy;
}

class Wykresy : public QDialog
{
    Q_OBJECT

public:
    explicit Wykresy(QWidget *parent = nullptr, QVector<int> WarunkiDoPolowow = QVector<int>(0), QVector<int> Temperatury = QVector<int>(0), QString Nazwa_Miasta = "Wrocław");
    ~Wykresy();

private:
    Ui::Wykresy *ui;
};

#endif // WYKRESY_H
