#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include "weatherday.h"
#include "weatherapp.h"
#include <QtNetwork/QNetworkAccessManager>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);
    void fetchToday();
    void fetchWeek();
signals:

    void todayWeatherUpdate(WeatherDay today);
    void weekWeatherUpdate(QList<WeatherDay> week);

public slots:

    void replyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;

};

#endif // NETWORKMANAGER_H
