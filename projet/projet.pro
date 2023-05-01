QT       += core gui
QT += sql
QT +=charts
QT += core gui printsupport
QT +=serialport
QT       += core gui sql network multimedia multimediawidgets charts printsupport widgets axcontainer serialport

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
    arduino.cpp \
    camerawidget.cpp \
    connexion.cpp \
    emp.cpp \
    employe.cpp \
    gestions.cpp \
    main.cpp \
    mainwindow.cpp \
    notification.cpp \
    oublier.cpp \
    qrcodegen.cpp \
    stat_comb.cpp

HEADERS += \
    arduino.h \
    camerawidget.h \
    connexion.h \
    emp.h \
    employe.h \
    gestions.h \
    mainwindow.h \
    notification.h \
    oublier.h \
    qrcodegen.h \
    stat_comb.h

FORMS += \
    emp.ui \
    gestions.ui \
    mainwindow.ui \
    oublier.ui \
    stat_comb.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../Downloads/interface.jpg \
    fond.jpg

RESOURCES += \
    Images.qrc \
    Ressource.qrc \
    image.qrc \
    ressoucess.qrc \
    stat_combo.qrc

