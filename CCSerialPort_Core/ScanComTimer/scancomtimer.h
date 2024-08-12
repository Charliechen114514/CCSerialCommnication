#ifndef SCANCOMTIMER_H
#define SCANCOMTIMER_H
#include <QTimer>
#include "CCSerialPort_Global.h"
class ScanComTimer {
public:
    ScanComTimer() = default;
    void setTimeInterval(const int mili_time);
signals:
    void shellScanTimer();

private:
    QTimer scan_timer;
};

#endif  // SCANCOMTIMER_H
