#include "weatherday.h"


WeatherDay::WeatherDay(QObject *parent)
    : QObject(parent), m_temp(0.0), m_wind(0.0), m_rain(0.0), m_cloud_cover(0)
{
}

double WeatherDay::getTemp() {
    return m_temp;
}


void WeatherDay::setTemp(double temp) {
    if (m_temp != temp) {
        m_temp = temp;
        emit tempChanged();
    }
}

double WeatherDay::getWind() {
    return m_wind;
}


void WeatherDay::setWind(double wind) {
    if (m_wind != wind) {
        m_wind = wind;
        emit windChanged();
    }
}

double WeatherDay::getPrecip() {
    return m_rain;
}


void WeatherDay::setPrecip(double precip) {
    if (m_rain != precip) {
        m_rain = precip;
        emit precipChanged();
    }
}


int WeatherDay::getCloudCover() {
    return m_cloud_cover;
}


void WeatherDay::setCloudCover(int cloud) {
    if (m_cloud_cover != cloud) {
        m_cloud_cover = cloud;
        emit cloudCoverChanged();
    }
}
