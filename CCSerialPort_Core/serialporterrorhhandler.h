#ifndef SERIALPORTERRORHHANDLER_H
#define SERIALPORTERRORHHANDLER_H
#include <QSerialPort>
#include "CCSerialPort_Global.h"

class SerialPortErrorHHandler {
public:
    SerialPortErrorHHandler() = delete;
    Q_DISABLE_COPY(SerialPortErrorHHandler);
    static QString getErrorString(QSerialPort::SerialPortError error);
};

#endif  // SERIALPORTERRORHHANDLER_H
