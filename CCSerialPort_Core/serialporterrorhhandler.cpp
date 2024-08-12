#include "serialporterrorhhandler.h"

QString SerialPortErrorHHandler::getErrorString(
    QSerialPort::SerialPortError error) {
    switch (error) {
        case QSerialPort::NoError:
            return "";
        case QSerialPort::DeviceNotFoundError:
            return "设备未打开，检查端口！";
        case QSerialPort::PermissionError:
            return "权限不足，可能是端口被占用！";
        case QSerialPort::OpenError:
            return "打开异常！";
        case QSerialPort::WriteError:
            return "写异常";
        case QSerialPort::ReadError:
            return "读异常";
        case QSerialPort::ResourceError:
            return "资源异常";
        case QSerialPort::UnsupportedOperationError:
            return "不被支持的操作！";
        case QSerialPort::UnknownError:
            return "未知操作！";
        case QSerialPort::TimeoutError:
            return "操作超时";
        case QSerialPort::NotOpenError:
            return "串口未打开！";
    }
    return "";
}
