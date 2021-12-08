QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

CONFIG += debug
CONFIG += force_debug_info

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller.cpp \
    controller_DFS.cpp \
    controller_MST.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow_admin.cpp \
    mainwindow_conferences.cpp \
    mainwindow_arenas.cpp \
    mainwindow_souvenirs.cpp \
    loginDialog.cpp \
    mainwindow_plan.cpp \
    stadium.cpp \
    importDialog.cpp \
    purchaseDialog.cpp

HEADERS += \
    seed.h \
    controller.h \
    mainwindow.h \
    loginDialog.h \
    stadium.h \
    importDialog.h \
    purchaseDialog.h

FORMS += \
    mainwindow.ui \
    loginDialog.ui \
    importDialog.ui \
    purchaseDialog.ui

RESOURCES += images/images.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
