#ifndef CCSERIAL_DEBUG_H
#define CCSERIAL_DEBUG_H
#include <QFile>
#include "CCSerialPort_Global.h"
class CCSerial_Debug {
public:
    CCSerial_Debug() = default;
    Q_DISABLE_COPY(CCSerial_Debug);
    virtual ~CCSerial_Debug() = default;
    enum class WriteTo { QtDebug_Console, For_Logging };
    virtual bool write(QString buffers);

protected:
    virtual bool           writeToConsole();
    virtual bool           writeToFile(QString filePath);
    std::unique_ptr<QFile> file;
};

class CCSerial_TimerDebug : public CCSerial_Debug {
public:
    struct TimerDebugLogger {
        DATA_HEAP_STR START_TIMER = "Timer start!\n";
        DATA_HEAP_STR STOP_TIMER  = "Timer Stop!\n";
        DATA_HEAP_STR TIME_OUT    = "Time Out! Call the hook function once!\n";
    };
    CCSerial_TimerDebug()          = default;
    virtual ~CCSerial_TimerDebug() = default;
    Q_DISABLE_COPY(CCSerial_TimerDebug);
    void tellStartTimer() {
        write(TimerDebugLogger::START_TIMER);
    }
    void tellStopTimer() {
        write(TimerDebugLogger::STOP_TIMER);
    }
    void tellTimeOut() {
        write(TimerDebugLogger::TIME_OUT);
    }
};

#endif  // CCSERIAL_DEBUG_H
