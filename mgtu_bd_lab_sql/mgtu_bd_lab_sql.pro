#-------------------------------------------------
#
# Project created by QtCreator 2018-02-23T00:47:47
#
#-------------------------------------------------

QT       += core gui sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mgtu_bd_lab_sql
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        database_widget.cpp \
    connectiondialog.cpp \
    treewidget.cpp

HEADERS  += database_widget.h \
    connectiondialog.h \
    treewidget.h

FORMS    += database_widget.ui \
    connectiondialog.ui

RESOURCES +=

DISTFILES += \
    fl.png \
    cont/fl.png \
    ../mgtu_bd_lab_sql_Debug/cont/12.png
