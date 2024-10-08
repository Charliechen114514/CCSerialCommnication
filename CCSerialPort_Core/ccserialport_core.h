#ifndef CCSERIALPORT_CORE_H
#define CCSERIALPORT_CORE_H
#include <QSerialPort>
#include <QTimer>
#include "CCSerailPortConfigures/ccserailportconfigures.h"
#include "CCSerialPort_Global.h"

class CCSerialPort_Core : public QObject {
    Q_OBJECT
public:
    CCSerialPort_Core(QObject* parent = nullptr);
    ~CCSerialPort_Core();
    Q_DISABLE_COPY(CCSerialPort_Core);
    void                   configPort(const CCSerailPortConfigures& configs);
    static QStringList     availPortsName();
    bool                   openCom(const QString& portName);
    void                   closeCom();
    bool                   isFine() const;
    bool                   isOpen() const;
    QString                errorString() const;
    CCSerailPortConfigures portConfigure() const;
    void                   setScanState(bool shellStartScan);
    std::optional<QString> doReadFromSerial();
    int                    doWriteToSerial(const QString& str);
    void                   shutDownCom();
    void                   startScan();
signals:
    void tellRefreshAvailablePorts();
    void tellNewReceivings();
    void tellCurrentComErrorOccur();

private:
    std::unique_ptr<QSerialPort> serial_port;
    QTimer                       scand_timer;
    struct TimerConfig {
        static constexpr short SCAN_PERIOD =
            INIT_PARAMS::TIMER_SCAN_AVAILABLE_COM;
    };
    QString recevings;
    // port related
    void initPort();
    void finiPort();
};

#endif  // CCSERIALPORT_CORE_H
