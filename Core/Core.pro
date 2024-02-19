CONFIG -= qt

TEMPLATE = lib

CONFIG += staticlib
CONFIG += c++20
QMAKE_CXXFLAGS += /WX

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Game.cpp \
    Playfield.cpp \
    Tetrimino.cpp

HEADERS += \
    Game.h \
    Matrix.h \
    Playfield.h \
    Tetrimino.h \

INSTALLS += target

