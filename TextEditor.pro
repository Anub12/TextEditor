QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = TextEditor
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    syntaxhighlighter.cpp

HEADERS += \
    mainwindow.h \
    syntaxhighlighter.h

FORMS += \
    mainwindow.ui
