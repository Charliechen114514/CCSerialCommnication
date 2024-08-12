#ifndef TIMERSENDWIDGET_H
#define TIMERSENDWIDGET_H
#include <QTimer>
#include <QWidget>
#include "CCSerialPort_Global.h"
namespace Ui {
class TimerSendWidget;
}

class TimerSendWidget : public QWidget {
    Q_OBJECT

public:
    struct TimerLimit {
        static constexpr short MIN_LIMIT = INIT_PARAMS::MIN_SEND_LIMIT;
        static constexpr short INIT      = INIT_PARAMS::INIT_PERIODLY_SEND;
    };

    explicit TimerSendWidget(QWidget *parent = nullptr);
    void setTimerState(bool st);
    ~TimerSendWidget();
    bool isTimerStart() const;
signals:
    void tellShellSend();
    void tellSetExternUi(bool st);

private:
    void                 checkSettings();
    Ui::TimerSendWidget *ui;
    QTimer               timerSend;
};

#endif  // TIMERSENDWIDGET_H
