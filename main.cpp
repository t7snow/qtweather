#include <QCoreApplication>
#include "weatherapp.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    WeatherApp weatherApp;

    return app.exec();
}
