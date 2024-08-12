#ifndef CCSERIAL_ABOUTCREATOR_H
#define CCSERIAL_ABOUTCREATOR_H
#include "CCSerialPort_Global.h"
struct AboutCreator {
    static constexpr short       _MINOR_VERSION = MINOR_VERSION;
    static constexpr short       _MAJOR_VERISON = MAJOR_VERISON;
    static constexpr const char* TEXT =
        "这是一个简单的基于QSerialPort置作的简单串口通信软件！\n";
    static constexpr const char* REPO =
        "https://github.com/Charliechen114514/CCSerialCommnication";
    static QString create() {
        return createVersionString() + createNormal() + createRepo();
    }

private:
    static QString createVersionString() {
        return "Version:" + QString::number(_MAJOR_VERISON) + '.' +
               QString::number(_MINOR_VERSION) + "\n";
    }

    static QString createNormal() {
        return TEXT;
    }

    static QString createRepo() {
        return QString("Repo: %1\n").arg(REPO);
    }
};

#endif  // CCSERIAL_ABOUTCREATOR_H
