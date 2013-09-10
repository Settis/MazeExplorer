#-------------------------------------------------
#
# Project created by QtCreator 2013-07-21T00:26:08
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mazeTest.cpp \
    robotTest.cpp \
    engineTest.cpp \
    determinRobotTest.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../engine/release/ -lengine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../engine/debug/ -lengine
else:unix: LIBS += -L$$OUT_PWD/../engine/ -lengine

INCLUDEPATH += $$PWD/../engine
DEPENDPATH += $$PWD/../engine

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../engine/release/engine.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../engine/debug/engine.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../engine/libengine.a

HEADERS += \
    mazeTest.h \
    robotTest.h \
    engineTest.h \
    determinRobotTest.h

QMAKE_CXXFLAGS += -std=c++0x
