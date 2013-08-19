#-------------------------------------------------
#
# Project created by QtCreator 2013-07-21T00:25:36
#
#-------------------------------------------------

QT       -= gui

TARGET = engine
TEMPLATE = lib
CONFIG += staticlib

SOURCES += engine.cpp \
    maze.cpp \
    robot.cpp \
    ilistener.cpp \
    robotcontainer.cpp \
    pureRandomRobot.cpp \
    progressLogger.cpp

HEADERS += engine.h \
    maze.h \
    robot.h \
    ilistener.h \
    robotcontainer.h \
    pureRandomRobot.h \
    progressLogger.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
QMAKE_CXXFLAGS += -std=c++0x
