QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Player1Controller.cpp \
    Player2Controller.cpp \
    RPSPlayer1Window.cpp \
    RPSPlayer2Window.cpp \
    main.cpp \
    RPSMainWindow.cpp \
    rpswithmachine.cpp

HEADERS += \
    Player1Controller.h \
    Player2Controller.h \
    RPSMainWindow.h \
    RPSPlayer1Window.h \
    RPSPlayer2Window.h \
    rpswithmachine.h

FORMS += \
    RPSMainWindow.ui \
    RPSPlayer1Window.ui \
    RPSPlayer2Window.ui \
    rpswithmachine.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc
