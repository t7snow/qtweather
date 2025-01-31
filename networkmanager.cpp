#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}, m_coord_manager(new QNetworkAccessManager(this)), m_weather_day(new WeatherDay(this))
{
    // for(int i=0; i< 7; ++i){
    //     WeatherDay *day = new WeatherDay(this);
    //     m_weather_week.append(day);
    // }
    // LocationManager *location_manager = new LocationManager(this);
    // connect(location_manager, &LocationManager::coordsReceived,
    //         this, &NetworkManager::onCoordsReceived);

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
        QJsonObject propertiesJsonObj = pointJsonObj["properties"].toObject();
        if (propertiesJsonObj.contains("periods")) {
            QJsonArray periods = propertiesJsonObj["periods"].toArray();
            int c =0;
            QList<WeatherDay*> week;
            for(const QJsonValue &periodValue : periods){

                QJsonObject period = periodValue.toObject();
                if(period["name"].toString().contains("Night")){
                    continue;
                }
                WeatherDay *weatherDay = new WeatherDay(this);

                weatherDay->setTemp(period["temperature"].toDouble());
                weatherDay->setWind(period["windSpeed"].toString().split(" ")[0].toDouble());
                //precip code
                double precip = 0;
                if (period.contains("probabilityOfPrecipitation")) {
                    QJsonObject pop = period["probabilityOfPrecipitation"].toObject();
                    if (pop.contains("value") && !pop["value"].isNull()) {
                        precip = pop["value"].toDouble(); // Return the probability as a double
                    }else{
                        precip = 0;
                    }
                    weatherDay->setPrecip(precip);
                }
                //precip code

                //cloudy code
                int cloudyInd = period["shortForecast"].toString().indexOf("Cloudy");
                if(cloudyInd != -1){
                    QString beforeCloud = period["detailedForecast"].toString().left(cloudyInd);
                    beforeCloud.endsWith("Mostly") ? weatherDay->setCloudCover(75) : (beforeCloud.endsWith("Partly") ? weatherDay->setCloudCover(50) : weatherDay->setCloudCover(100));

                }else{
                    weatherDay->setCloudCover(0);
                }
                //cloudy code

                if(c ==0 ){
                    emit todayWeatherUpdate(weatherDay);
                    week.append(weatherDay);
                    continue;
                }
                week.append(weatherDay);
                if(c==7){
                    emit weekWeatherUpdate(week);
                    return;
                }
                c++;
            }
        }
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
            connect(reply, &QNetworkReply::finished, this, [this, reply]() {
                this->forecastReplyFinished(reply);
            });

        }
    }

}


void NetworkManager::fetchToday(double lat, double longi){
    QString coordUrl = QString("https://api.weather.gov/points/{%1},{%2}").arg(lat).arg(longi);
    QNetworkRequest request(QUrl("https://api.weather.com/data"));
    QNetworkReply *reply = m_coord_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        this->pointReplyFinished(reply);
    });
}


void NetworkManager::onCoordsReceived(double lat, double longi){

    fetchToday(lat, longi);


}

