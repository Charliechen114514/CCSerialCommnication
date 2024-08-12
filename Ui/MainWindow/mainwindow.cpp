#include "mainwindow.h"
#include "CCSerial_AboutCreator.h"
#include "Utils/FileSaver/ccserailfilesaver.h"
#include "Utils/MessageBoxHandler/messageboxhandler.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui_handler.initMainWindowUi();
    initCoreMemory();
    initConnections();
}

void MainWindow::initCoreMemory() {
    serial_core = std::make_unique<CCSerialPort_Core>();
}

void MainWindow::initConnections() {
    connect(serial_core.get(), &CCSerialPort_Core::tellRefreshAvailablePorts,
            this, &MainWindow::rescanComSerial);
    connect(serial_core.get(), &CCSerialPort_Core::tellNewReceivings, this,
            &MainWindow::handleReceivings);
    connect(ui->checkBox_showHex, &QCheckBox::stateChanged, this,
            &MainWindow::hexDisplay);
    connect(ui->action_save_current_frame, &QAction::triggered, this,
            &MainWindow::saveCurrent);
    connect(ui->action_save_all, &QAction::triggered, this,
            &MainWindow::saveWhole);
    connect(ui->timer_widget, &TimerSendWidget::tellShellSend, this,
            &MainWindow::doWritingToSerial);
    connect(ui->timer_widget, &TimerSendWidget::tellSetExternUi, this,
            &MainWindow::handleTimelySend);
    connect(ui->action_about, &QAction::triggered, this,
            &MainWindow::displayAbout);
}

void MainWindow::displayAbout() {
    MessageBoxHandler::About::showAbout(this, AboutCreator::create());
}

void MainWindow::hexDisplay() {
    ui_handler.setHexMode();
}

void MainWindow::rescanComSerial() {
    ui_handler.freshComInfo();
}

void MainWindow::handleReceivings() {
    if (const auto receivings = serial_core->doReadFromSerial(); !receivings) {
        qDebug() << "Error in reading!";
        MessageBoxHandler::ErrorInform::tellError(
            "发生错误！", serial_core->errorString(), this);
        return;
    } else {
        qDebug() << receivings.value();
        ui_handler.updateStatusLabel(receivings.value().size(),
                                     StatusBarWidget::StatusBarRole::RECEIVE);
        ui_handler.appendReceiving(receivings.value());
    }
}

void MainWindow::handleTimelySend(bool st) {
    ui_handler.doSetAbleClear(!st);
}

void MainWindow::doWritingToSerial() {
    const auto buffers = ui->send_edit->toPlainText();
    if (buffers.isEmpty()) {
        return;
    }
    int res = serial_core->doWriteToSerial(buffers);
    if (!res) {
        MessageBoxHandler::ErrorInform::tellError(
            "发生错误！", serial_core->errorString(), this);
        return;
    }
    ui_handler.updateStatusLabel(res, StatusBarWidget::StatusBarRole::SEND);
    ui_handler.appendGiving(buffers);
}

void MainWindow::opposeCommStatus() {
    if (ui_handler.getStatus() ==
        UiMainWindowManagerHandler::Status::ON_COMMUNICATIONS)
        stopCommunication();
    else if (ui_handler.getStatus() ==
             UiMainWindowManagerHandler::Status::OFF_COMMUNICATIONS)
        startCommunications();
    else
        return;
}

void MainWindow::clearOutPut() {
    ui_handler.clearBrowser(CommunicationDecorations::CleanMethod::CLEAN_TEMP);
}

void MainWindow::deleteOutPut() {
    if (!MessageBoxHandler::AskForQuery::query(
            "是否删除所有输出?", "他们真的会丢失很久的！", this)) {
        return;
    }

    ui_handler.clearBrowser(
        CommunicationDecorations::CleanMethod::CLEAN_RESTORE);
}

void MainWindow::prev_hist() {
    ui_handler.toPrevHist();
}
void MainWindow::next_hist() {
    ui_handler.toNextHist();
}

void MainWindow::startCommunications() {
    QString current_com_name = ui->com_comboBox->currentText();
    auto    configs          = ui_handler.getConfigureFromUi();
    serial_core->configPort(configs);
    if (!serial_core->openCom(current_com_name)) {
        MessageBoxHandler::ErrorInform::tellError(
            "发生错误！", serial_core->errorString(), this);
        return;
    }
    qDebug() << "串口启动！";
    ui_handler.setStatus(UiMainWindowManagerHandler::Status::ON_COMMUNICATIONS);
    serial_core->setScanState(false);
}

void MainWindow::stopCommunication() {
    if (!serial_core->isOpen()) return;
    serial_core->closeCom();
    qDebug() << "串口关闭！";
    ui_handler.setStatus(
        UiMainWindowManagerHandler::Status::OFF_COMMUNICATIONS);
    serial_core->setScanState(true);
}

void MainWindow::saveCurrent() {
    QString res   = ui_handler.getCurrent();
    QString place = CCSerailFileSaver::getSavePlace(this);
    if (place.isEmpty()) return;
    if (!CCSerailFileSaver::save(res, place)) {
        MessageBoxHandler::ErrorInform::tellError("出问题了！", "保存失败！",
                                                  this);
    }
}

void MainWindow::saveWhole() {
    QString res   = ui_handler.getWhole();
    QString place = CCSerailFileSaver::getSavePlace(this);
    if (place.isEmpty()) return;
    if (!CCSerailFileSaver::save(res, place)) {
        MessageBoxHandler::ErrorInform::tellError("出问题了！", "保存失败！",
                                                  this);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
