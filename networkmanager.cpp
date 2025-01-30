#include "networkmanager.h"
#include "locationmanager.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}, m_coord_manager(new QNetworkAccessManager(this)), m_weather_day(new WeatherDay(this))
{
    for(int i=0; i< 7; ++i){
        WeatherDay *day = new WeatherDay(this);
        m_weather_week.append(day);
    }
    LocationManager *location_manager = new LocationManager(this);
    connect(location_manager, &LocationManager::coordsReceived,
            this, &NetworkManager::onCoordsReceived);

}

void NetworkManager::forecastReplyFinished(QNetworkReply *reply){

    if(reply->error()){
        qWarning() << "Network error!" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    reply->deleteLater();
    QJsonParseError *error = new QJsonParseError();
    QJsonDocument jsonReply = QJsonDocument::fromJson(responseData, error);
    if(error){
        qWarning() << "Parsing JSON error!" << error->errorString();
    }

    QJsonObject pointJsonObj = jsonReply.object();
    qDebug() << "Response: " << pointJsonObj;

    if(pointJsonObj.contains("forecast")){
        QJsonObject forecastJsonObj = pointJsonObj["properties"].toObject();

    }



}
void NetworkManager::pointReplyFinished(QNetworkReply *reply){

    if(reply->error()){
        qWarning() << "Network error!" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    reply->deleteLater();
    QJsonParseError *error = new QJsonParseError();
    QJsonDocument jsonReply = QJsonDocument::fromJson(responseData, error);
    if(error){
        qWarning() << "Parsing JSON error!" << error->errorString();
    }

    // call the second piece to get the actual forecast:

    QJsonObject pointJsonObj = jsonReply.object();
    qDebug() << "Response: " << pointJsonObj;

    if(pointJsonObj.contains("properties")){
        QJsonObject propJsonObj = pointJsonObj["properties"].toObject();
        if(propJsonObj.contains("forecast")){
            QString forecastUrl = propJsonObj["forecast"].toString();
            QNetworkRequest request((QUrl(forecastUrl)));
            QNetworkReply *reply = m_forecast_manager->get(request);
            connect(reply, &QNetworkReply::finished,this, &NetworkManager::forecastReplyFinished);

        }
    }

}


void NetworkManager::fetchToday(double lat, double longi){
    QString coordUrl = QString("https://api.weather.gov/points/{%1},{%2}").arg(lat).arg(longi);
    QNetworkRequest request(QUrl("https://api.weather.com/data"));
    QNetworkReply *reply = m_coord_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &NetworkManager::pointReplyFinished);
}


void NetworkManager::onCoordsReceived(double lat, double longi){

    fetchToday(lat, longi);
    fetchWeek(lat, longi);

}

