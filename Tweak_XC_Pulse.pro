INCLUDEPATH += D:\program_files\Qt\Qt5.12.3\5.12.3\mingw73_64\include\qwt

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets  serialport

CONFIG(debug, debug|release):LIBS += -L"D:\program_files\Qt\Qt5.12.3\5.12.3\msvc2017_64\lib" -lqwtd
CONFIG(release, debug|release):LIBS += -L"D:\program_files\Qt\Qt5.12.3\5.12.3\msvc2017_64\lib" -lqwt

#LIBS += -L"D:\QT5.12\5.12.0\mingw73_64\lib" -lqwt

CONFIG += qwt
DEFINES += QT_DLL QWT_DLL
#LIBS += -L"D:\QT5.12\5.12.0\mingw73_64\lib" -lqwtd
#LIBS += -L"D:\QT5.12\5.12.0\mingw73_64\lib"  -lqwt
#INCLUDEPATH += D:\QT5.12\5.12.0\mingw73_64\include\qwt

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO


TARGET = Tweak_XC_Pulse
TEMPLATE = app

SOURCES += main.cpp\
    data_processing.cpp \
        mainwindow.cpp \
    aboutdialog.cpp \
    report_generater.cpp \
    serialport_decoder.cpp \
    ex_qthread.cpp \
    calculator.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    data_processing.h \
    report_generater.h \
    serialport_decoder.h \
    ex_qthread.h \
    calculator.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

RESOURCES += resource.qrc

RC_FILE += resourceScript.rc



