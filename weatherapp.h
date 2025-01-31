#ifndef WEATHERAPP_H
#define WEATHERAPP_H

#include <QObject>
#include "weatherday.h"

class WeatherApp : public QObject
{
    Q_OBJECT
public:
    explicit WeatherApp(QObject *parent = nullptr);

    QList<WeatherDay> week;
    void display(WeatherDay today, QList<WeatherDay> week);

signals:



private slots:

    void todayDataUpdate(WeatherDay *today);
    void weekDataUpdate(QList<WeatherDay*> week);
    // void run();

};

#endif // WEATHERAPP_H
