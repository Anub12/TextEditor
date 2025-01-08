QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = TextEditor
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    syntaxhighlighter.cpp \
    texteditor.cpp

HEADERS += \
    mainwindow.h \
    syntaxhighlighter.h \
    texteditor.h

FORMS += \
    mainwindow.ui
