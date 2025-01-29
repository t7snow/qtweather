#include "locationmanager.h"

LocationManager::LocationManager(QObject *parent)
    : QObject{parent}, m_source(QGeoPositionInfoSource::createDefaultSource(this))
{
    if(m_source){
        connect(m_source, &QGeoPositionInfoSource::positionUpdated, this, &LocationManager::finished);
        m_source->startUpdates();
    }
}

void LocationManager::finished(QGeoPositionInfo &info){
    QGeoCoordinate coord = info.coordinate();
    double lat = coord.latitude();
    double longitude = coord.longitude();

    emit coordsReceived(lat, longitude);
}


