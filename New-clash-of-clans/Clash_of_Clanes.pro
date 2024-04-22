QT       += core gui
   QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    cannon.cpp \
    fence1.cpp \
    health.cpp \
    main.cpp \
    game.cpp \
    townhall.cpp \
    troop.cpp \
    workers.cpp

HEADERS += \
    bullet.h \
    cannon.h \
    fence1.h \
    game.h \
    health.h \
    townhall.h \
    troop.h \
    workers.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc \
    res.qrc
