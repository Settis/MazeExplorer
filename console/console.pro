#-------------------------------------------------
#
# Project created by QtCreator 2013-07-21T16:41:14
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = mazeExplorer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../engine/release/ -lengine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../engine/debug/ -lengine
else:unix: LIBS += -L$$OUT_PWD/../engine/ -lengine

INCLUDEPATH += $$PWD/../engine
DEPENDPATH += $$PWD/../engine

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../engine/release/engine.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../engine/debug/engine.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../engine/libengine.a
