#-------------------------------------------------
#
# Project created by QtCreator 2017-07-06T11:30:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
unix:TARGET = ChineseChessFour
win32:TARGET = ../ChineseChessFour
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    Observer.cpp \
    control.cpp \
    Model/AI.cpp \
    Model/Model.cpp \
    View/chesspieces.cpp \
    View/getpkmode.cpp \
    View/m1_welcome.cpp \
    View/mainwindow.cpp \
    View/sleep.cpp \
    View/view.cpp \
    View/viewchessboard.cpp \
    ViewModel/ViewModel.cpp \
    ViewModel/Commands/MoveCommand.cpp \
    ViewModel/Commands/PossibleMoveCommand.cpp \
    ViewModel/Commands/StartCommand.cpp \
    Model/ai_test.cpp

HEADERS  += ChessBoard.h \
    command.h \
    Observer.h \
    control.h \
    Any.h \
    Model/AI.h \
    Model/Model.h \
    View/chesspieces.h \
    View/getpkmode.h \
    View/m1_welcome.h \
    View/mainwindow.h \
    View/sleep.h \
    View/view.h \
    View/viewchessboard.h \
    ViewModel/ViewModel.h \
    ViewModel/Commands/DerivedCommand.h \
    ViewModel/Commands/MoveCommand.h \
    ViewModel/Commands/PossibleMoveCommand.h \
    ViewModel/Commands/StartCommand.h \
    possiblemoveposition.h \
    Model/ai_test.h 

FORMS    += View/chesspieces.ui \
    View/getpkmode.ui \
    View/m1_welcome.ui \
    View/mainwindow.ui \
    View/viewchessboard.ui 

RESOURCES += \
    pic.qrc \
