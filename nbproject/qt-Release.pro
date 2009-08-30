TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = phed
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
QT = core gui
SOURCES += LineStrip.cpp PropertyBrowser.cpp PropertiesWindow.cpp Polygon.cpp main.cpp EditorScene.cpp Object.cpp EditorWindow.cpp
HEADERS += PropertiesWindow.h Object.h PropertyBrowser.h Polygon.h EditorScene.h EditorWindow.h LineStrip.h
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