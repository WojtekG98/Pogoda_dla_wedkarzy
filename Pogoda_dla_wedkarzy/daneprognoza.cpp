#include "daneprognoza.h"

DanePrognoza::DanePrognoza(QObject *parent) : QObject(parent)
{
    temp.fill(0,5);
    speed.fill(0, 5);
    deg.fill(0,5);
    pressure.fill(0,5);
    icon.fill(0,5);

}

QString DanePrognoza::StringToIcon(const QString icon_txt, uint8_t flag){
    if (flag==0)
    {
        if ( icon_txt == "01d")
            return ":/ikony_openweather/ikony/01d.png";
        else if ( icon_txt == "01n")
            return ":/ikony_openweather/ikony/01n.png";
        else if ( icon_txt == "02d")
            return ":/ikony_openweather/ikony/02d.png";
        else if ( icon_txt == "02n")
            return ":/ikony_openweather/ikony/02n.png";
        else if ( icon_txt == "03d")
            return ":/ikony_openweather/ikony/03d.png";
        else if ( icon_txt == "03n")
            return ":/ikony_openweather/ikony/03d.png";
        else if ( icon_txt == "04d")
            return ":/ikony_openweather/ikony/04d.png";
        else if ( icon_txt == "04n")
            return ":/ikony_openweather/ikony/04d.png";
        else if ( icon_txt == "09d")
            return ":/ikony_openweather/ikony/09d.png";
        else if ( icon_txt == "09n")
            return ":/ikony_openweather/ikony/09d.png";
        else if ( icon_txt == "10d")
            return ":/ikony_openweather/ikony/10d.png";
        else if ( icon_txt == "10n")
            return ":/ikony_openweather/ikony/10n.png";
        else if ( icon_txt == "11d")
            return ":/ikony_openweather/ikony/11d.png";
        else if ( icon_txt == "11n")
            return ":/ikony_openweather/ikony/11d.png";
        else if ( icon_txt == "13d")
            return ":/ikony_openweather/ikony/13d.png";
        else if ( icon_txt == "13n")
            return ":/ikony_openweather/ikony/13d.png";
        else if ( icon_txt == "50d")
            return ":/ikony_openweather/ikony/50d.png";
        else if ( icon_txt == "50n")
            return ":/ikony_openweather/ikony/50d.png";
        else
            return "Brak ikony!";
    }
    else if(flag == 1)
    {
        if ( icon_txt == "01d")
            return ":/ikony_qt/icons/weather-sunny.png";
        else if ( icon_txt == "01n")
            return ":/ikony_qt/icons/weather-sunny.png";
        else if ( icon_txt == "02d")
            return ":/ikony_qt/icons/weather-sunny-very-few-clouds.png";
        else if ( icon_txt == "02n")
            return ":/ikony_qt/icons/weather-sunny-very-few-clouds.png";
        else if ( icon_txt == "03d")
            return ":/ikony_qt/icons/weather-overcast.png";
        else if ( icon_txt == "03n")
            return ":/ikony_qt/icons/weather-overcast.png";
        else if ( icon_txt == "04d")
            return ":/ikony_qt/icons/weather-overcast.png";
        else if ( icon_txt == "04n")
            return ":/ikony_qt/icons/weather-overcast.png";
        else if ( icon_txt == "09d")
            return ":/ikony_qt/icons/weather-showers.png";
        else if ( icon_txt == "09n")
            return ":/ikony_qt/icons/weather-showers.png";
        else if ( icon_txt == "10d")
            return ":/ikony_qt/icons/weather-showers.png";
        else if ( icon_txt == "10n")
            return ":/ikony_qt/icons/weather-showers.png";
        else if ( icon_txt == "11d")
            return ":/ikony_qt/icons/weather-storm.png";
        else if ( icon_txt == "11n")
            return ":/ikony_qt/icons/weather-storm.png";
        else if ( icon_txt == "13d")
            return ":/ikony_qt/icons/weather-icy.png";
        else if ( icon_txt == "13n")
            return ":/ikony_qt/icons/weather-icy.png";
        else if ( icon_txt == "50d")
            return ":/ikony_qt/icons/weather-fog.png";
        else if ( icon_txt == "50n")
            return ":/ikony_qt/icons/weather-fog.png";
        else
            return "Brak ikony!";
    }
    else
        return "Błędna flaga!";
}

void DanePrognoza::prognozaZmieniona(QJsonDocument dane)
{
    QDateTime aktualna = QDateTime::currentDateTime();
    QJsonObject jo = dane.object();
    QJsonArray list = jo["list"].toArray();
    QString aktualna_data_str = aktualna.toString("yyyy-MM-dd") + QString(" 12:00:00");
    for(int i = 0; i < 5; i++){
        aktualna_data_str = aktualna.addDays(i+1).toString("yyyy-MM-dd") + QString(" 12:00:00");
        while(list.first().toObject()["dt_txt"].toString() != aktualna_data_str && list.size() != 1)
            list.removeFirst();
        QJsonObject main = list.first()["main"].toObject();
        QJsonObject wind = list.first()["wind"].toObject();
        QJsonArray weather = list.first()["weather"].toArray();
        temp[i] = (main["temp"].toDouble() - Kelvin);
        speed[i] = (wind["speed"].toDouble());
        deg[i] = (wind["deg"].toInt());
        pressure[i] = (main["pressure"].toInt());
        icon[i] = (weather.first()["icon"].toString());
    }
}
