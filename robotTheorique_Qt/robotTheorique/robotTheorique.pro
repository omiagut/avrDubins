#-------------------------------------------------
#
# Project created by QtCreator 2022-11-19T14:33:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = robotTheorique
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calculs.cpp \
    graph.cpp \
    robot.cpp \
    scene.cpp \
    vue.cpp \
    courbes/cercle.cpp \
    courbes/courbe.cpp \
    courbes/parametres.cpp

HEADERS  += mainwindow.h \
    calculs.h \
    graph.h \
    robot.h \
    scene.h \
    vue.h \
    courbes/cercle.h \
    courbes/courbe.h \
    courbes/parametres.h

DISTFILES += \
    robotTheorique.pro.user
