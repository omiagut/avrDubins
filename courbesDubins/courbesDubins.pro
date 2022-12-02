#-------------------------------------------------
#
# Project created by QtCreator 2022-10-09T18:56:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = courbesDubins
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    courbes/cercle.cpp \
    courbes/courbe.cpp \
    courbes/parametres.cpp \
    vue.cpp \
    scene.cpp \
    graph.cpp

HEADERS  += mainwindow.h \
    courbes/cercle.h \
    courbes/courbe.h \
    courbes/parametres.h \
    vue.h \
    scene.h \
    graph.h
