QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# 头文件搜索路径
INCLUDEPATH += $$PWD/Headers

CONFIG += c++17
RC_ICONS = resource/notix.ico
DESTDIR = $$PWD/bin

# SOURCES
SOURCES += \
    Sources/HttpMgr.cpp \
    Sources/global.cpp \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/logindialog.cpp \
    Sources/registerdialog.cpp

# HEADERS
HEADERS += \
    Headers/HttpMgr.h \
    Headers/global.h \
    Headers/mainwindow.h \
    Headers/logindialog.h \
    Headers/registerdialog.h \
    Headers/singleton.h

# UI 文件
FORMS += \
    Forms/mainwindow.ui \
    Forms/logindialog.ui \
    Forms/registerdialog.ui

# 资源文件
RESOURCES += \
    resource/loginpic.qrc \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
