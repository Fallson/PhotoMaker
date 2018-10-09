HEADERS=./ResPublisher/respublisher.h

SOURCES=./ResPublisher/main.cpp \
        ./ResPublisher/respublisher.cpp

FORMS=./ResPublisher/respublisher.ui

# win32 {
#     SOURCES += hellowin.cpp
# }
# unix {
#     SOURCES += hellounix.cpp
# }
MOC_DIR = ./res_moc_tmps
OBJECTS_DIR = ./res_obj_tmps
RCC_DIR = ./res_rcc_tmps
UI_DIR = ./res_ui_tmps

RESOURCES     = ./ResPublisher/respublisher.qrc
RC_FILE       = ./ResPublisher/ResPublisher.pro.rc
ICON          = ./ResPublisher/ResPublisher.icns

INCLUDEPATH += ./ResPublisher
win32:LIBS += Winspool.lib User32.lib shell32.lib Dbghelp.lib
CONFIG += stl qt
QT += xml
