QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14
INCLUDEPATH += C:/Opencv/opencv/build/include

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(release, debug|release)
{
    LIBS+= -LC:/Opencv/opencv/VS/lib -lopencv_core340 -lopencv_highgui340 -lopencv_imgcodecs340 -lopencv_videoio340 -lopencv_imgproc340
}

CONFIG(debug, debug|release)
{
    LIBS+= -LC:/Opencv/opencv/VS/lib -lopencv_core340d -lopencv_highgui340d -lopencv_imgcodecs340d -lopencv_videoio340d -lopencv_imgproc340d
}

SOURCES += \
    aboutprogram.cpp \
    applypast.cpp \
    fileoperations.cpp \
    main.cpp \
    mainwindow.cpp \
    opencv_.cpp \
    pictureoperations.cpp \
    resimonizle.cpp

HEADERS += \
    aboutprogram.h \
    applypast.h \
    fileoperations.h \
    mainwindow.h \
    opencv_.h \
    pictureoperations.h \
    resimonizle.h

FORMS += \
    aboutprogram.ui \
    applypast.ui \
    mainwindow.ui \
    resimonizle.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Files.qrc
