#ifndef WEATHERDAY_H
#define WEATHERDAY_H

#include <QObject>

class WeatherDay : public QObject
{
    Q_OBJECT
public:
    explicit WeatherDay(QObject *parent = nullptr);
    Q_PROPERTY(double temp READ getTemp WRITE setTemp NOTIFY tempChanged FINAL);
    Q_PROPERTY(double humidity READ getHumidity WRITE setHumidity NOTIFY humidityChanged FINAL);
    Q_PROPERTY(double precip READ getPrecip WRITE setPrecip NOTIFY precipChanged FINAL);
    Q_PROPERTY(double cloud_cover READ getCloudCover WRITE setCloudCover NOTIFY cloudCoverChanged FINAL);

    double getTemp();
    void setTemp();

    double getHumidity();
    void setHumidity();

    double getPrecip();
    void setPrecip();

    double getCloudCover();
    void setCloudCover();


signals:

    void tempChanged();
    void humidityChanged();
    void precipChanged();
    void cloudCoverChanged();

private:
    double m_temp;
    double m_humidity;
    double m_rain;
    double m_cloud_cover;


};

#endif // WEATHERDAY_H
