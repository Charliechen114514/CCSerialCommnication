#include "timersendwidget.h"
#include <QValidator>
#include "Utils/MessageBoxHandler/messageboxhandler.h"
#include "ui_timersendwidget.h"
TimerSendWidget::TimerSendWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::TimerSendWidget) {
    ui->setupUi(this);
    ui->timer_lineEdit->setValidator(new QIntValidator(this));
    ui->timer_lineEdit->setText(QString::number(TimerLimit::INIT));
    timerSend.setInterval(TimerLimit::INIT);
    connect(&timerSend, &QTimer::timeout, this,
            &TimerSendWidget::tellShellSend);
    connect(ui->timer_lineEdit, &QLineEdit::returnPressed, this,
            &TimerSendWidget::checkSettings);
    connect(ui->timer_checkBox, &QCheckBox::clicked, this,
            &TimerSendWidget::setTimerState);
    connect(ui->timer_checkBox, &QCheckBox::clicked, this,
            &TimerSendWidget::tellSetExternUi);
}

void TimerSendWidget::setTimerState(bool st) {
    st ? timerSend.start() : timerSend.stop();
}

bool TimerSendWidget::isTimerStart() const {
    return timerSend.isActive();
}

void TimerSendWidget::checkSettings() {
    bool ok      = false;
    int  milisec = ui->timer_lineEdit->text().toInt(&ok);
    if (!ok) {
        MessageBoxHandler::ErrorInform::tellError(
            "！", "非法的输入！how do you reach here! Tell Me Buuuuuuuugs!",
            this);
        return;
    }
    if (milisec < TimerSendWidget::TimerLimit::MIN_LIMIT) {
        MessageBoxHandler::ErrorInform::tellError("！", "不允许发送过快！",
                                                  this);
        milisec = TimerLimit::MIN_LIMIT;
    }

    timerSend.setInterval(milisec);
}

TimerSendWidget::~TimerSendWidget() {
    delete ui;
}
