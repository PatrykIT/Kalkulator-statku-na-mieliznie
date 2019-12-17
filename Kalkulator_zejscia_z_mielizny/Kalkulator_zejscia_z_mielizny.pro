#-------------------------------------------------
#
# Project created by QtCreator 2018-05-14T19:29:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kalkulator_zejscia_z_mielizny
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


CONFIG += c++14
CONFIG += static

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    statek.cpp \
    interpolacja.cpp \
    tests.cpp \
    tabela_dzialania_widget.cpp

HEADERS += \
        mainwindow.h \
    statek.h \
    interpolacja.h \
    tests.h \
    tabela_dzialania_widget.h

FORMS += \
        mainwindow.ui \
    tabela_dzialania_widget.ui

#RESOURCES += \
#    pictures.qrc

RESOURCES += \
    ship_pictures.qrc
