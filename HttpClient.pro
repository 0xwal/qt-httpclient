QT -= gui
QT += network

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


HTTPCLIENTPATH=$$PWD

INCLUDEPATH += $$HTTPCLIENTPATH/include/

SOURCES += \
        $$HTTPCLIENTPATH/source/HttpClient.cpp \
        $$HTTPCLIENTPATH/source/HttpResponse.cpp \
        $$HTTPCLIENTPATH/source/HttpRequest.cpp \
        $$HTTPCLIENTPATH/source/HttpUtils.cpp \
        $$HTTPCLIENTPATH/source/HttpGlobalRequestOptions.cpp \
        $$HTTPCLIENTPATH/source/HttpJsonContent.cpp \
        $$HTTPCLIENTPATH/source/HttpQueryContent.cpp


HEADERS += \
        $$HTTPCLIENTPATH/include/HttpClient.h \
        $$HTTPCLIENTPATH/include/HttpGlobalRequestOptions.h \
        $$HTTPCLIENTPATH/include/HttpContentInterface.h \
        $$HTTPCLIENTPATH/include/HttpRequest.h \
        $$HTTPCLIENTPATH/include/HttpResponse.h \
        $$HTTPCLIENTPATH/include/HttpUtils.h \
        $$HTTPCLIENTPATH/include/HttpJsonContent.h
        $$HTTPCLIENTPATH/include/HttpQueryContent.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
win32{
    httpClientLib.path = $$[QT_INSTALL_LIBS]
    httpClientLib.files = $$OUT_PWD/debug/libHttpClient.a main.cpp
    INSTALLS += httpClientLib
}
!isEmpty(target.path): INSTALLS += target
