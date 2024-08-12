#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "CCSerialPort_Core/ccserialport_core.h"
#include "CCSerialPort_Global.h"
#include "Ui/MainWindowUiHandler/uimainwindowmanagerhandler.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void opposeCommStatus();
    void clearOutPut();
    void prev_hist();
    void next_hist();
    void displayAbout();
    void hexDisplay();
    void deleteOutPut();
    void saveCurrent();
    void saveWhole();
    ~MainWindow();

public slots:
    void rescanComSerial();

private slots:
    BIND_UI_WIDGET void on_btn_start_serial_clicked() {
        opposeCommStatus();
    }

    BIND_UI_WIDGET void on_btn_send_data_clicked() {
        doWritingToSerial();
    }

    BIND_UI_WIDGET void on_btn_clear_output_clicked() {
        clearOutPut();
    }

    BIND_UI_WIDGET void on_btn_toPrev_clicked() {
        prev_hist();
    }

    BIND_UI_WIDGET void on_btn_toNext_clicked() {
        next_hist();
    }

    void on_btn_clearRestore_clicked() {
        deleteOutPut();
    }

private:
    void initCoreMemory();
    void initConnections();
    void startCommunications();
    void stopCommunication();
    void doWritingToSerial();
    void handleReceivings();
    void handleTimelySend(bool st);
    friend class UiMainWindowManagerHandler;
    friend class InitUiMainWindowConfig;
    std::unique_ptr<CCSerialPort_Core> serial_core;
    UiMainWindowManagerHandler         ui_handler{this};
    Ui::MainWindow                    *ui;
};
#endif  // MAINWINDOW_H
