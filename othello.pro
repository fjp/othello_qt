#-------------------------------------------------
#
# Project created by QtCreator 2016-02-02T01:19:28
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = othello
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        board/board.cpp \
        board/disk.cpp \
        board/square.cpp \
        player/player.cpp \
        player/humanplayer.cpp \
        player/computerplayer.cpp \
        ai.cpp \
        referee.cpp \
        ui/uisquare.cpp \
        ui/uigamescene.cpp \
    ui/uidisk.cpp

HEADERS  += mainwindow.h \
        board/board.h \
        board/disk.h \
        board/square.h \
        player/player.h \
        player/humanplayer.h \
        player/computerplayer.h \
        ai.h \
        referee.h \
        ui/uisquare.h \
        ui/uigamescene.h \
    ui/uidisk.h

FORMS    += mainwindow.ui
