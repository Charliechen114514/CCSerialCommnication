#include "ccserialport_core.h"
#include <QSerialPortInfo>
#include <QThread>
#include "CCSerialPort_Core/serialporterrorhhandler.h"
#include "qdebug.h"
CCSerialPort_Core::CCSerialPort_Core(QObject* parent) : QObject(parent) {
    initPort();
    scand_timer.setInterval(TimerConfig::SCAN_PERIOD);
    connect(&scand_timer, &QTimer::timeout, this,
            &CCSerialPort_Core::tellRefreshAvailablePorts);
    connect(serial_port.get(), &QSerialPort::readyRead, this,
            &CCSerialPort_Core::tellNewReceivings);
    setScanState(true);
}

void CCSerialPort_Core::setScanState(bool st) {
    st ? scand_timer.start() : scand_timer.stop();
}

void CCSerialPort_Core::initPort() {
    serial_port = std::make_unique<QSerialPort>();
}

void CCSerialPort_Core::finiPort() {
    if (serial_port->isOpen()) {
        serial_port->clear();
        serial_port->close();
    }
}

void CCSerialPort_Core::configPort(const CCSerailPortConfigures& configs) {
    configs.configPort(serial_port.get());
}

CCSerailPortConfigures CCSerialPort_Core::portConfigure() const {
    return PortConfiguresFactory::create(serial_port.get());
}

bool CCSerialPort_Core::openCom(const QString& portName) {
    serial_port->setPortName(portName);
    serial_port->open(QIODevice::ReadWrite);
    return serial_port->isOpen();
}

bool CCSerialPort_Core::isFine() const {
    return serial_port->error() == QSerialPort::NoError;
}

bool CCSerialPort_Core::isOpen() const {
    return serial_port->isOpen();
}

std::optional<QString> CCSerialPort_Core::doReadFromSerial() {
    return serial_port->isOpen()
               ? std::optional{QString(serial_port->readAll()).toUtf8()}
               : std::nullopt;
}

int CCSerialPort_Core::doWriteToSerial(const QString& str) {
    if (!serial_port->isOpen()) return false;
    qDebug() << "Write: " << str;
    int res = serial_port->write(str.toUtf8());

    if (!serial_port->waitForBytesWritten(30000)) {
        qDebug() << "命令发送异常" << serial_port->errorString();
        return 0;
    }
    return res;
}

QString CCSerialPort_Core::errorString() const {
    return SerialPortErrorHHandler::getErrorString(serial_port->error());
}

QStringList CCSerialPort_Core::availPortsName() {
    QStringList l{};
    const auto  ports = QSerialPortInfo::availablePorts();
    for (const auto& port : ports) l << port.portName();
    return l;
}

void CCSerialPort_Core::closeCom() {
    finiPort();
}

CCSerialPort_Core::~CCSerialPort_Core() {
    finiPort();
}
