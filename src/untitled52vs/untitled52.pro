#-------------------------------------------------
#
# Project created by QtCreator 2014-07-16T09:51:47
#
#-------------------------------------------------

QT       += core gui multimedia winextras multimediawidgets webkitwidgets network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = APlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    trackListMeneger.cpp \
    reparationFragment.cpp \
    mycondextmenu.cpp \
    fileinfodialog.cpp \
    contextmenutabwidget.cpp \
    myid3tegextractor.cpp \
    dialogrenameplaylist.cpp \
    dialogdeleteplaylist.cpp \
    tracklistformat.cpp \
    vkauth.cpp \
    contextmenuopenfile.cpp \
    myqlistwidget.cpp \
    mymediaplayer.cpp \
    audioeffectwindow.cpp \
    windowplaylist.cpp \
    fftvisualwidget.cpp \
    artistinfowiki.cpp \
    bufferengwindow.cpp \
    playlistmeneger.cpp \
    xmlplaylistmeneger.cpp \
    myqslider.cpp \
    progressbarmusic.cpp

HEADERS  += mainwindow.h \
    trackListMeneger.h \
    reparationFragment.h \
    mycondextmenu.h \
    fileinfodialog.h \
    contextmenutabwidget.h \
    myid3tegextractor.h \
    dialogrenameplaylist.h \
    dialogdeleteplaylist.h \
    tracklistformat.h \
    vkauth.h \
    contextmenuopenfile.h \
    myqlistwidget.h \
    mymediaplayer.h \
    audioeffectwindow.h \
    windowplaylist.h \
    fftvisualwidget.h \
    artistinfowiki.h \
    bufferengwindow.h \
    playlistmeneger.h \
    xmlplaylistmeneger.h \
    myqslider.h \
    progressbarmusic.h

FORMS    += mainwindow.ui \
    tracklistformat.ui \
    fileinfodialog.ui \
    dialogrenameplaylist.ui \
    dialogdeleteplaylist.ui \
    vkauth.ui \
    audioeffectwindow.ui \
    windowplaylist.ui \
    fftvisualwidget.ui \
    artistinfowiki.ui \
    bufferengwindow.ui

RESOURCES += \
    icon.qrc

#-----------------------------------------------------------
#Подключение библиотеки id3lib
#-----------------------------------------------------------
#win32: LIBS += -L$$PWD/../../../libs/SystemDynamicLib_x86/ -lid3lib

#INCLUDEPATH += $$PWD/../../../libs/id3lib/bin/include
#DEPENDPATH += $$PWD/../../../libs/id3lib/bin/include


#-----------------------------------------------------------
# Подключение библиотеки Bass
#-----------------------------------------------------------
LIBS += -LC:\libs\SystemDynamicLib_x86

CONFIG(release, debug|release): LIBS += -lbass
CONFIG(debug, debug|release): LIBS += -lbass

INCLUDEPATH += C:\libs\bass-2-4-win\c
DEPENDPATH += C:\libs\bass-2-4-win\c

#-----------------------------------------------------------
# Подключение библиотеки Bass FLAC
#-----------------------------------------------------------
LIBS += -LC:\libs\SystemDynamicLib_x86

CONFIG(release, debug|release): LIBS += -lbassflac
CONFIG(debug, debug|release): LIBS += -lbassflac

INCLUDEPATH += C:\libs\bassFlac\c
DEPENDPATH += C:\libs\bassFlac\c

#-----------------------------------------------------------
# Подключение библиотеки Bass WMA
#-----------------------------------------------------------
LIBS += -LC:\libs\SystemDynamicLib_x86

CONFIG(release, debug|release): LIBS += -lbasswma
CONFIG(debug, debug|release): LIBS += -lbasswma

INCLUDEPATH += C:\libs\bassWMA\c
DEPENDPATH += C:\libs\bassWMA\c

#-----------------------------------------------------------
# Подключение библиотеки Bass FX
#-----------------------------------------------------------
LIBS += -LC:\libs\SystemDynamicLib_x86

CONFIG(release, debug|release): LIBS += -lbass_fx
CONFIG(debug, debug|release): LIBS += -lbass_fx

INCLUDEPATH += C:\libs\bassFX\C
DEPENDPATH += C:\libs\bassFX\C

#-----------------------------------------------------------
# Подключение библиотеки Bass Tags
#-----------------------------------------------------------
LIBS += -LC:\libs\SystemDynamicLib_x86

CONFIG(release, debug|release): LIBS += -ltags
CONFIG(debug, debug|release): LIBS += -ltags

INCLUDEPATH += C:\libs\tags17\c
DEPENDPATH +=  C:\libs\tags17\c

OTHER_FILES +=

DISTFILES +=
