#ifndef CCSERAILPORTCONFIGURES_H
#define CCSERAILPORTCONFIGURES_H
#include <QSerialPort>
#include "CCSerialPort_Global.h"
struct CCSerailPortConfigures {
    QSerialPort::BaudRate    baudRate = QSerialPort::Baud115200;
    QSerialPort::DataBits    dataBits = QSerialPort::Data8;
    QSerialPort::FlowControl flowControl =
        QSerialPort::FlowControl::NoFlowControl;
    QSerialPort::Parity   parity   = QSerialPort::NoParity;
    QSerialPort::StopBits stopBits = QSerialPort::StopBits::OneStop;

    void configPort(MEMORY_PASS_ONLY QSerialPort* port) const;
};

struct PortConfiguresFactory {
    static CCSerailPortConfigures create(MEMORY_PASS_ONLY QSerialPort* port);
};

struct ConfigureConvertor {
#define CONVERTOR(X, type)                           \
    struct X##Convertor {                            \
    public:                                          \
        static QString     convert(type kind);       \
        static type        convert(const char* str); \
        static QStringList labels();                 \
    }

    CONVERTOR(BaudRate, QSerialPort::BaudRate);
    CONVERTOR(DataBits, QSerialPort::DataBits);
    CONVERTOR(Parity, QSerialPort::Parity);
    CONVERTOR(StopBits, QSerialPort::StopBits);
#undef CONVERTOR
};

#endif  // CCSERAILPORTCONFIGURES_H
