#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include "weatherday.h"
#include "weatherapp.h"


class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);
    void fetchToday(double lat, double longi);
    // void fetchWeek(double lat, double longi);
signals:

    void todayWeatherUpdate(WeatherDay *today);
    void weekWeatherUpdate(QList<WeatherDay*> week);

public slots:

    void onCoordsReceived(double lat, double longi);
    void pointReplyFinished(QNetworkReply *reply);
    void forecastReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_coord_manager;
    QNetworkAccessManager *m_forecast_manager;
    WeatherDay *m_weather_day;
    QList<WeatherDay*> m_weather_week;

};

#endif // NETWORKMANAGER_H
