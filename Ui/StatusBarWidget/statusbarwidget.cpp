#include "statusbarwidget.h"
#include "ui_statusbarwidget.h"

StatusBarWidget::StatusBarWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::StatusBarWidget) {
    ui->setupUi(this);
    initTimer();
}

void StatusBarWidget::setReceivingCounts(const int& rec) {
    ui->receive_label->setText(LabelSettingsFactory::createReceivingLabel(rec));
}
void StatusBarWidget::setSendCounts(const int& send) {
    ui->send_label->setText(LabelSettingsFactory::createSendLabel(send));
}

void StatusBarWidget::updateTimeLabel() {
    ui->time_label->setText(LabelSettingsFactory::createTimeLabel());
}

void StatusBarWidget::initTimer() {
    periodly_fresh_timer.setInterval(1000);
    periodly_fresh_timer.start();
    connect(&periodly_fresh_timer, &QTimer::timeout, this,
            &StatusBarWidget::updateTimeLabel);
}

StatusBarWidget::~StatusBarWidget() {
    delete ui;
}
