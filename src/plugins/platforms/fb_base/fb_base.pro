#-------------------------------------------------
#
# Project created by QtCreator 2009-11-05T13:22:31
#
#-------------------------------------------------

#QT       -= core gui
TARGET = fb_base
#load(qt_plugin)

DESTDIR = $$QT.gui.plugins/graphicssystems

TEMPLATE = lib

#DEFINES += STATIC_LIBRARY
CONFIG += staticlib

SOURCES += fb_base.cpp

HEADERS += fb_base.h

target.path += $$[QT_INSTALL_PLUGINS]/graphicssystems
INSTALLS += target
