#include "weatherapp.h"
#include "networkmanager.h"
#include "locationmanager.h"
#include <QCoreApplication>
#include <QDebug>

WeatherApp::WeatherApp(QObject *parent)
    : QObject(parent)
{
    // Create a LocationManager instance
    LocationManager *locationManager = new LocationManager(this);

    // Create a NetworkManager instance
    NetworkManager *networkManager = new NetworkManager(this);

    // Connect LocationManager's coordsReceived signal to NetworkManager's onCoordsReceived slot
    connect(locationManager, &LocationManager::coordsReceived,
            networkManager, &NetworkManager::onCoordsReceived);

    // Connect NetworkManager's signals to WeatherApp's slots
    connect(networkManager, &NetworkManager::todayWeatherUpdate,
            this, &WeatherApp::todayDataUpdate);
    connect(networkManager, &NetworkManager::weekWeatherUpdate,
            this, &WeatherApp::weekDataUpdate);

}

void WeatherApp::todayDataUpdate(WeatherDay *today) {
    qDebug() << "Today's Weather:";
    qDebug() << "Temperature:" << today->getTemp() << "°F";
    qDebug() << "Wind Speed:" << today->getWind() << "mph";
    qDebug() << "Precipitation:" << today->getPrecip() << "%";
    qDebug() << "Cloud Cover:" << today->getCloudCover() << "%";
    qDebug() << "--------------------------";
}

void WeatherApp::weekDataUpdate(QList<WeatherDay*> week) {
    qDebug() << "Weekly Weather Forecast:";
    for (int i = 0; i < week.size(); ++i) {
        qDebug() << "Day" << (i + 1) << ":";
        qDebug() << "Temperature:" << week[i]->getTemp() << "°F";
        qDebug() << "Wind Speed:" << week[i]->getWind() << "mph";
        qDebug() << "Precipitation:" << week[i]->getPrecip() << "%";
        qDebug() << "Cloud Cover:" << week[i]->getCloudCover() << "%";
        qDebug() << "--------------------------";
    }
}


