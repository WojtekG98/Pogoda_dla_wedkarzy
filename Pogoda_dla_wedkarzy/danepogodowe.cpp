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

double DanePogodowe::TemperaturaMin() const
{
    return this->temp_min;
}

double DanePogodowe::PredkoscWiatru() const
{
    return this->speed;
}

unsigned int DanePogodowe::Wilgotnosc() const
{
    return this->humidity;
}

unsigned int DanePogodowe::Cisnienie() const
{
    return this->pressure;
}

unsigned int DanePogodowe::KatWiatru() const
{
    return this->deg;
}

QTime DanePogodowe::CzasWschod() const
{
    return this->sunrise;
}

QTime DanePogodowe::CzasZachod() const
{
    return this->sunset;
}

QString DanePogodowe::NazwaMiasta() const
{
    return this->name;
}

QString DanePogodowe::OpisPogody() const
{
    return this->description;
}

QString DanePogodowe::IkonaPogody(uint8_t flag) const
{
    if (flag==0)
    {
        if (this->icon == "01d")
            return ":/ikony_openweather/ikony/01d.png";
        else if (this->icon == "01n")
            return ":/ikony_openweather/ikony/01n.png";
        else if (this->icon == "02d")
            return ":/ikony_openweather/ikony/02d.png";
        else if (this->icon == "02n")
            return ":/ikony_openweather/ikony/02n.png";
        else if (this->icon == "03d")
            return ":/ikony_openweather/ikony/03d.png";
        else if (this->icon == "03n")
            return ":/ikony_openweather/ikony/03d.png";
        else if (this->icon == "04d")
            return ":/ikony_openweather/ikony/04d.png";
        else if (this->icon == "04n")
            return ":/ikony_openweather/ikony/04d.png";
        else if (this->icon == "09d")
            return ":/ikony_openweather/ikony/09d.png";
        else if (this->icon == "09n")
            return ":/ikony_openweather/ikony/09d.png";
        else if (this->icon == "10d")
            return ":/ikony_openweather/ikony/10d.png";
        else if (this->icon == "10n")
            return ":/ikony_openweather/ikony/10n.png";
        else if (this->icon == "11d")
            return ":/ikony_openweather/ikony/11d.png";
        else if (this->icon == "11n")
            return ":/ikony_openweather/ikony/11d.png";
        else if (this->icon == "13d")
            return ":/ikony_openweather/ikony/13d.png";
        else if (this->icon == "13n")
            return ":/ikony_openweather/ikony/13d.png";
        else if (this->icon == "50d")
            return ":/ikony_openweather/ikony/50d.png";
        else if (this->icon == "50n")
            return ":/ikony_openweather/ikony/50d.png";
        else
            return "Brak ikony!";
    }
    else if(flag == 1)
    {
        if (this->icon == "01d")
            return ":/ikony_qt/icons/weather-sunny.png";
        else if (this->icon == "01n")
            return ":/ikony_qt/icons/weather-sunny.png";
        else if (this->icon == "02d")
            return ":/ikony_qt/icons/weather-sunny-very-few-clouds.png";
        else if (this->icon == "02n")
            return ":/ikony_qt/icons/weather-sunny-very-few-clouds.png";
        else if (this->icon == "03d")
            return ":/ikony_qt/icons/weather-overcast.png";
        else if (this->icon == "03n")
            return ":/ikony_qt/icons/weather-overcast.png";
        else if (this->icon == "04d")
            return ":/ikony_qt/icons/weather-overcast.png";
        else if (this->icon == "04n")
            return ":/ikony_qt/icons/weather-overcast.png";
        else if (this->icon == "09d")
            return ":/ikony_qt/icons/weather-showers.png";
        else if (this->icon == "09n")
            return ":/ikony_qt/icons/weather-showers.png";
        else if (this->icon == "10d")
            return ":/ikony_qt/icons/weather-showers.png";
        else if (this->icon == "10n")
            return ":/ikony_qt/icons/weather-showers.png";
        else if (this->icon == "11d")
            return ":/ikony_qt/icons/weather-storm.png";
        else if (this->icon == "11n")
            return ":/ikony_qt/icons/weather-storm.png";
        else if (this->icon == "13d")
            return ":/ikony_qt/icons/weather-icy.png";
        else if (this->icon == "13n")
            return ":/ikony_qt/icons/weather-icy.png";
        else if (this->icon == "50d")
            return ":/ikony_qt/icons/weather-fog.png";
        else if (this->icon == "50n")
            return ":/ikony_qt/icons/weather-fog.png";
        else
            return "Brak ikony!";
    }
    else
        return "Błędna flaga!";
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
