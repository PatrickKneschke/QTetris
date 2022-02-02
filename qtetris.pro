TARGET  = qtetris

TEMPLATE = app
QT		+= widgets multimedia

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += ui_qtetris.h qtetris.h piece.h
SOURCES += main.cpp qtetris.cpp piece.cpp
