#ifndef STATUSBARWIDGET_H
#define STATUSBARWIDGET_H
#include <QDateTime>
#include <QTimer>
#include <QWidget>
#include "CCSerialPort_Global.h"

namespace Ui {
class StatusBarWidget;
}

class StatusBarWidget : public QWidget {
    Q_OBJECT

public:
    explicit StatusBarWidget(QWidget* parent = nullptr);
    void setReceivingCounts(const int& rec);
    void setSendCounts(const int& send);
    enum class StatusBarRole { RECEIVE, SEND };
    ~StatusBarWidget();

private:
    struct LabelSettingsFactory {
        DATA_HEAP_STR  RECEIVING_PREFIX = "收到";
        static QString createReceivingLabel(const int& rec) {
            return QString("%1: %2")
                .arg(RECEIVING_PREFIX)
                .arg(QString::number(rec));
        }

        DATA_HEAP_STR  SEND_PREFIX = "发送";
        static QString createSendLabel(const int& send) {
            return QString("%1: %2")
                .arg(SEND_PREFIX)
                .arg(QString::number(send));
        }

        DATA_HEAP_STR  TIME_PREFIX = "时间: ";
        static QString createTimeLabel() {
            return QString("%1: %2")
                .arg(TIME_PREFIX)
                .arg(QDateTime::currentDateTime().toString());
        }
    };
    QTimer               periodly_fresh_timer;
    void                 updateTimeLabel();
    void                 initTimer();
    Ui::StatusBarWidget* ui;
};

#endif  // STATUSBARWIDGET_H
