#-------------------------------------------------
#
# Project created by QtCreator 2016-05-26T15:41:56
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cpp_project_2_1
TEMPLATE = app
RC_ICONS = icon.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    list_item_form.cpp \
    info_form.cpp \
    person.cpp \
    adressbook.cpp \
    classmate.cpp \
    colleague.cpp \
    friend.cpp \
    relative.cpp

HEADERS  += mainwindow.h \
    list_item_form.h \
    info_form.h \
    person.h \
    addressbook.h \
    classmate.h \
    colleague.h \
    friend.h \
    relative.h

FORMS    += mainwindow.ui \
    list_item_form.ui \
    info_form.ui

DISTFILES +=

RESOURCES += \
    icon.qrc


