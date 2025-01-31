#ifndef LOCATIONMANAGER_H
#define LOCATIONMANAGER_H

#include <QObject>
#include <QGeoPositionInfoSource>
#include <QGeoPositionInfo>

class LocationManager : public QObject
{
    Q_OBJECT
public:
    explicit LocationManager(QObject *parent = nullptr);
    // void getCoords();

signals:
    void coordsReceived(double lat, double longitude);

public slots:
    void finished(const QGeoPositionInfo &info);

private:
    QGeoPositionInfoSource *m_source;
};

#endif // LOCATIONMANAGER_H
