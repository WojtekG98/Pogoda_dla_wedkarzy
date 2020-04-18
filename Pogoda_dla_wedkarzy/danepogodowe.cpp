#include "danepogodowe.h"

DanePogodowe::DanePogodowe(QObject *parent) : QObject(parent)
{

}

void DanePogodowe::daneZmienione(QJsonDocument dane)
{
    QJsonObject jo = dane.object();
    QJsonObject main = jo["main"].toObject();
    this->feels_like = main["feels_like"].toDouble()-Kelvin;
    this->humidity = main["humidity"].toInt();
    this->pressure = main["pressure"].toInt();
    this->temp = main["temp"].toDouble()-Kelvin;
    this->temp_max = main["temp_max"].toDouble()-Kelvin;
    this->temp_min = main["temp_min"].toDouble()-Kelvin;
    QJsonObject sys = jo["sys"].toObject();
    QTime sunrise_tmp(0,0,0), sunset_tmp(0,0,0);
    sunrise_tmp = sunrise_tmp.addSecs(int(sys["sunrise"].toInt()));
    sunset_tmp = sunset_tmp.addSecs(sys["sunset"].toInt());
    this->sunrise = sunrise_tmp;
    this->sunset = sunset_tmp;
    QJsonObject wind = jo["wind"].toObject();
    this->deg = wind["deg"].toInt();
    this->speed = wind["speed"].toDouble();
    QJsonArray weather = jo["weather"].toArray();
    this->description = weather.first()["description"].toString();
    this->icon = weather.first()["icon"].toString();
    this->name = jo["name"].toString();
}
double DanePogodowe::Temperatura() const
{
    return this->temp;
}
double DanePogodowe::TemperaturaOdczuwalna() const
{
    return this->feels_like;
}
double DanePogodowe::TemperaturaMax() const
{
    return this->temp_max;
}

QString DanePogodowe::NazwaMiasta() const
{
    return this->name;
}

QString DanePogodowe::IkonaPogody() const
{
   if (this->icon == "01d")
       return ":/new/prefix1/icons/weather-sunny.png";
   else if (this->icon == "01n")
       return ":/new/prefix1/icons/weather-sunny.png";
   else if (this->icon == "02d")
       return ":/new/prefix1/icons/weather-sunny-very-few-clouds.png";
   else if (this->icon == "02n")
       return ":/new/prefix1/icons/weather-sunny-very-few-clouds.png";
   else if (this->icon == "03d")
       return ":/new/prefix1/icons/weather-overcast.png";
   else if (this->icon == "03n")
       return ":/new/prefix1/icons/weather-overcast.png";
   else if (this->icon == "04d")
       return ":/new/prefix1/icons/weather-overcast.png";
   else if (this->icon == "04n")
       return ":/new/prefix1/icons/weather-overcast.png";
   else if (this->icon == "09d")
       return ":/new/prefix1/icons/weather-showers.png";
   else if (this->icon == "09n")
       return ":/new/prefix1/icons/weather-showers.png";
   else if (this->icon == "10d")
       return ":/new/prefix1/icons/weather-showers.png";
   else if (this->icon == "10n")
       return ":/new/prefix1/icons/weather-showers.png";
   else if (this->icon == "11d")
       return ":/new/prefix1/icons/weather-storm.png";
   else if (this->icon == "11n")
       return ":/new/prefix1/icons/weather-storm.png";
   else if (this->icon == "13d")
       return ":/new/prefix1/icons/weather-snow.png";
   else if (this->icon == "13n")
       return ":/new/prefix1/icons/weather-snow.png";
   else if (this->icon == "50d")
       return ":/new/prefix1/icons/weather-fog.png";
   else if (this->icon == "50n")
       return ":/new/prefix1/icons/weather-fog.png";
   else
       return "Brak ikony!";
}
QString DanePogodowe::Wyswietl()
{
    return  "name = " +
            this->name +
            "\nfeels_like = " +
            QString::number(this->feels_like) +
            "\nhumidity = " +
            QString::number(this->humidity) +
            "%\npressure = " +
            QString::number(this->pressure) +
            "\ntemp = " +
            QString::number(this->temp) +
            "\ntemp_max = " +
            QString::number(this->temp_max) +
            "\ntemp_min = " +
            QString::number(this->temp_min) +
            "\nsunrise = " +
            this->sunrise.toString() +
            "\nsunset = " +
            this->sunset.toString() +
            "\ndeg = " +
            QString::number(this->deg) +
            "\nspeed = " +
            QString::number(this->speed) +
            "\ndesc = " +
            this->description +
            "\nicon = " +
            this->icon;
}
