QT = core network positioning

CONFIG += c++17 sdk_no_version_check

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_INFO_PLIST = Info.plist

macx {
    LIBS += -framework CoreLocation
    QMAKE_INFO_PLIST = Info.plist
}

SOURCES += \
        locationmanager.cpp \
        main.cpp \
        networkmanager.cpp \
        weatherapp.cpp \
        weatherday.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    locationmanager.h \
    networkmanager.h \
    weatherapp.h \
    weatherday.h


