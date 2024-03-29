TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = phed
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
QT = core gui
SOURCES += Body.cpp Rect.cpp Polygon.cpp main.cpp EditorWindow.cpp EditorView.cpp PropertyBrowser.cpp Circle.cpp Fixture.cpp Object.cpp World.cpp ContactListener.cpp Point.cpp
HEADERS += Object.h PropertyBrowser.h ScopedPointer.h Polygon.h Body.h Circle.h Fixture.h World.h Rect.h ContactListener.h EditorWindow.h EditorView.h Point.h
FORMS +=
RESOURCES += icons.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
