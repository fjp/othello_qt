#-------------------------------------------------
#
# Project created by QtCreator 2016-02-02T01:19:28
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = othello
TEMPLATE = app


SOURCES += main/main.cpp\
        main/mainwindow.cpp \
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
        ui/uidisk.cpp \
        gamelogic/gameengine.cpp \
        gamelogic/gameevent.cpp

HEADERS  += main/mainwindow.h \
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
        ui/uidisk.h \
        gamelogic/gameengine.h \
        gamelogic/gameevent.h

FORMS    += main/mainwindow.ui
