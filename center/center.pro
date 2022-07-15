QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    car.cpp \
    car_add.cpp \
    chat.cpp \
    client_select.cpp \
    main.cpp \
    mainwindow.cpp \
    reserv.cpp \
    reserv_add.cpp \
    thread.cpp \
    tour.cpp \
    tour_add.cpp \
    user.cpp \
    user_add.cpp

HEADERS += \
    car.h \
    car_add.h \
    chat.h \
    client_select.h \
    database.h \
    mainwindow.h \
    reserv.h \
    reserv_add.h \
    tcp.h \
    thread.h \
    tour.h \
    tour_add.h \
    user.h \
    user_add.h

FORMS += \
    car.ui \
    car_add.ui \
    chat.ui \
    client_select.ui \
    mainwindow.ui \
    reserv.ui \
    reserv_add.ui \
    tour.ui \
    tour_add.ui \
    user.ui \
    user_add.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
