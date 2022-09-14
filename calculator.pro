QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


#CONFIG += c++17 console
CONFIG += c++17 console sanitizer sanitize_address
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        #Display_plus_Text.cpp \
        MyController.cpp \
        MyFunction.cpp \
        #Save_25_08.cpp \
        MyModel.cpp \
        MyView.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    MyController.h \
    MyFunction.h \
    MyModel.h \
    MyView.h