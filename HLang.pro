TEMPLATE = app
TARGET = HLang
QT += core gui widgets network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += console
INCLUDEPATH += ./HBase\
               ./HGui
HEADERS += ./HBase/*.h \
           ./HBase/HData/*.h \
           ./HBase/HLogic/*.h \
           ./HBase/HNetwork/*.h \
           ./HGui/*.h        

SOURCES += ./HBase/*.cpp \
           ./HBase/HData/*.cpp \
           ./HBase/HLogic/*.cpp \
           ./HBase/HNetwork/*.cpp \
           ./HGui/*.cpp \
           ./main.cpp
FORMS += ./HGui/*.ui
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
