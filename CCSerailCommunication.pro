QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS += Resources/application_icons/application_icon.ico

INCLUDEPATH += \
    Ui/TimerSendWidget/

SOURCES += \
    CCSerailPortConfigures/ccserailportconfigures.cpp \
    CCSerialPort_Core/ccserialport_core.cpp \
    CCSerialPort_Core/serialporterrorhhandler.cpp \
    Debug/TimerDebug/ccserial_debug.cpp \
    Main/main.cpp \
    Ui/CommunicationDecorations/communicationdecorations.cpp \
    Ui/CoreAdapter/ccserialportui_initialsources.cpp \
    Ui/CoreAdapter/uiinitializeradapter.cpp \
    Ui/MainWindow/mainwindow.cpp \
    Ui/MainWindowUiHandler/MainWindowInitializer/inituimainwindowconfig.cpp \
    Ui/MainWindowUiHandler/uimainwindowmanagerhandler.cpp \
    Ui/MenuSettingsAction/ccserailuisettingsaction.cpp \
    Ui/StatusBarWidget/statusbarwidget.cpp \
    Ui/StyleSheetsHandler/stylesheetshandler.cpp \
    Ui/TimerSendWidget/timersendwidget.cpp \
    Utils/FileSaver/ccserailfilesaver.cpp \
    Utils/MessageBoxHandler/messageboxhandler.cpp

HEADERS += \
    CCSerailPortConfigures/ccserailportconfigures.h \
    CCSerialPort_Core/ccserialport_core.h \
    CCSerialPort_Core/serialporterrorhhandler.h \
    CCSerialPort_Global.h \
    CCSerial_AboutCreator.h \
    Debug/TimerDebug/ccserial_debug.h \
    Ui/CommunicationDecorations/communicationdecorations.h \
    Ui/CoreAdapter/ccserialportui_initialsources.h \
    Ui/CoreAdapter/uiinitializeradapter.h \
    Ui/MainWindow/mainwindow.h \
    Ui/MainWindowUiHandler/MainWindowInitializer/inituimainwindowconfig.h \
    Ui/MainWindowUiHandler/uimainwindowmanagerhandler.h \
    Ui/MenuSettingsAction/ccserailuisettingsaction.h \
    Ui/StatusBarWidget/statusbarwidget.h \
    Ui/StyleSheetsHandler/stylesheetshandler.h \
    Ui/TimerSendWidget/timersendwidget.h \
    Utils/FileSaver/ccserailfilesaver.h \
    Utils/MessageBoxHandler/messageboxhandler.h

FORMS += \
    Ui/MainWindow/mainwindow.ui \
    Ui/StatusBarWidget/statusbarwidget.ui \
    Ui/TimerSendWidget/timersendwidget.ui

DEFINES += \
    DEBUG_CHECK_TIMER_WORK \
    PURE_RELEASE

DEFINES += \
    MAJOR_VERISON=1 \
    MINOR_VERSION=0


release{
contains(DEFINES, PURE_RELEASE){
DEFINES += QT_NO_WARNING_OUTPUT
DEFINES += QT_NO_DEBUG_OUTPUT
}
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/light_themes/dark/darkstyle.qrc \
    Resources/light_themes/light/lightstyle.qrc \
    resources.qrc

