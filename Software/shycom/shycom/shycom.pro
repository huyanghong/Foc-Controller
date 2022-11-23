QT       += core gui serialport opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lopengl32 \
        -lglu32 \



CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SerialThread.cpp \
    main.cpp \
    mainwindow.cpp \
    mycurvewidget.cpp \
    myserialwidget.cpp \
    mydockwidget.cpp \
    mymotorwidget.cpp

HEADERS += \
    SerialThread.h \
    mainwindow.h \
    mycurvewidget.h \
    myserialwidget.h \
    mydockwidget.h \
    mymotorwidget.h

FORMS += \
    mainwindow.ui


#INCLUDEPATH += /usr/local/qwt-6.1.3/include
#LIBS += -L "/usr/local/qwt-6.1.3/lib/" -lqwt

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

#DEFINES += QT_DLL QWT_DLL

LIBS +=  -L "C:\Qt\Qt5.12.12\5.12.12\mingw73_64\lib" -lqwtd

#LIBS +=  -L "C:\Qt\Qt5.12.12\5.12.12\mingw73_64\lib" -lqwt

INCLUDEPATH += "C:\Qt\Qt5.12.12\5.12.12\mingw73_64\include\qwt"
