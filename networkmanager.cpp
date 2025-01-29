#include "networkmanager.h"
#include "locationmanager.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}, m_manager(new QNetworkAccessManager(this))
{
    LocationManager *location_manager;
    connect(location_manager, &LocationManager::coordsReceived,
            this, &NetworkManager::onCoordsReceived);

}

void NetworkManager::replyFinished(QNetworkReply *reply){

}


void NetworkManager::fetchToday(double lat, double longi){
    QString url = QString("https://api.weather.gov/points/{%1},{%2}").arg(lat).arg(longi);
    QNetworkRequest request(QUrl("https://api.weather.com/data"));
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &NetworkManager::replyFinished);
}

void NetworkManager::fetchWeek(double lat, double longi){

    QNetworkRequest request(QUrl("https://api.weather.com/data"));
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &NetworkManager::replyFinished);
}


void NetworkManager::onCoordsReceived(double lat, double longi){

    fetchToday(lat, longi);
    fetchWeek(lat, longi);

}

