#include <QCoreApplication>
#include <QLocationPermission>
#include "weatherapp.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    WeatherApp weatherApp;

    QLocationPermission perm;
    perm.setAccuracy(QLocationPermission::Approximate);
    app.requestPermission(perm, [](const QPermission &p) {
        qDebug() << "Permission status:" << p.status();
    });

    return app.exec();
}
