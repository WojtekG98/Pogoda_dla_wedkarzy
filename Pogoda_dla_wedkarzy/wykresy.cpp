#include "wykresy.h"
#include "ui_wykresy.h"

Wykresy::Wykresy(QWidget *parent, QVector<int> WarunkiDoPolowow, QVector<int> Temperatury, QString Nazwa_Miasta):
    QDialog(parent),
    ui(new Ui::Wykresy)
{
    ui->setupUi(this);
    ui->Nazwa_Miasta->setText(Nazwa_Miasta);
    QVector<QCPGraphData> WarunkiDoPolowowDane(6), TemperaturyDane(6);
    double now = QDateTime::currentDateTime().toTime_t();
    for (int i=0; i < 6; ++i)
    {
      TemperaturyDane[i].key = now + 24*3600*i;
      TemperaturyDane[i].value = Temperatury[i];
      WarunkiDoPolowowDane[i].key = now + 24*3600*i;
      WarunkiDoPolowowDane[i].value = WarunkiDoPolowow[i];
    }
    int min_temp = *std::min_element(Temperatury.constBegin(), Temperatury.constEnd()),
        max_temp = *std::max_element(Temperatury.constBegin(), Temperatury.constEnd());
    ui->WykresTemperatur->addGraph();
    ui->WykresTemperatur->xAxis->setRange(now, now+24*3600*5);
    ui->WykresTemperatur->yAxis->setRange(min_temp - 5, max_temp + 5);
    ui->WykresTemperatur->graph()->data()->set(TemperaturyDane);
    ui->WykresWarunkowDoPolowow->addGraph();
    ui->WykresWarunkowDoPolowow->xAxis->setRange(now, now+24*3600*5);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTick(5, "idealne");
    textTicker->addTick(3, "umiarkowane");
    textTicker->addTick(0, "złe");
    ui->WykresWarunkowDoPolowow->yAxis->setTicker(textTicker);
    ui->WykresWarunkowDoPolowow->graph()->data()->set(WarunkiDoPolowowDane);
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("ddd");
    ui->WykresWarunkowDoPolowow->xAxis->setTicker(dateTicker);
    ui->WykresTemperatur->xAxis->setTicker(dateTicker);
    ui->WykresTemperatur->yAxis->setLabel("T[°C]");
    ui->WykresWarunkowDoPolowow->xAxis->setLabel("Dni");
    ui->WykresTemperatur->xAxis->setLabel("Dni");
    ui->WykresTemperatur->plotLayout()->insertRow(0);
    ui->WykresTemperatur->plotLayout()->addElement(0, 0, new QCPTextElement(ui->WykresTemperatur, "Temperatura", QFont("sans", 12, QFont::Bold)));
    ui->WykresWarunkowDoPolowow->plotLayout()->insertRow(0);
    ui->WykresWarunkowDoPolowow->plotLayout()->addElement(0, 0, new QCPTextElement(ui->WykresWarunkowDoPolowow, "Warunki do połowów ryb", QFont("sans", 12, QFont::Bold)));

}

Wykresy::~Wykresy()
{
    delete ui;
}
