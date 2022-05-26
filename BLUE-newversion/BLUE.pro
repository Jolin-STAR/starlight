QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += resources_big
QT+=multimedia
QT+=multimediawidgets

QMAKE_CXXFLAGS += /MP
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Player.cpp \
    PlaylistModel.cpp \
    QMediaPlaylist.cpp \
    QPlaylistParser.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Player.h \
    PlaylistModel.h \
    QMediaPlaylist.h \
    QMediaPlaylist_p.h \
    QPlaylistParser.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc

