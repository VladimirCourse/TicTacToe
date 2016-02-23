#-------------------------------------------------
#
# Project created by QtCreator 2015-08-18T13:03:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TicTacToe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    figure.cpp \
    game.cpp \
    bot.cpp \
    optiondialog.cpp

HEADERS  += mainwindow.h \
    figure.h \
    game.h \
    constraints.h \
    bot.h \
    optiondialog.h

FORMS    += mainwindow.ui \
    optiondialog.ui
