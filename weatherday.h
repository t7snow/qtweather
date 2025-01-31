#ifndef WEATHERDAY_H
#define WEATHERDAY_H

#include <QObject>

class WeatherDay : public QObject
{
    Q_OBJECT
public:
    explicit WeatherDay(QObject *parent = nullptr);
    Q_PROPERTY(double temp READ getTemp WRITE setTemp NOTIFY tempChanged FINAL);
    Q_PROPERTY(double wind READ getWind WRITE setWind NOTIFY windChanged FINAL);
    Q_PROPERTY(double precip READ getPrecip WRITE setPrecip NOTIFY precipChanged FINAL);
    Q_PROPERTY(double cloud_cover READ getCloudCover WRITE setCloudCover NOTIFY cloudCoverChanged FINAL);

    double getTemp();
    void setTemp(double temp);

    double getWind();
    void setWind(double wind);

    double getPrecip();
    void setPrecip(double precip);

    int getCloudCover();
    void setCloudCover(int cloud);


signals:

    void tempChanged();
    void windChanged();
    void precipChanged();
    void cloudCoverChanged();

private:
    double m_temp;
    double m_wind;
    double m_rain;
    //75 mostly
    //50 partly
    int m_cloud_cover;


};

#endif // WEATHERDAY_H
