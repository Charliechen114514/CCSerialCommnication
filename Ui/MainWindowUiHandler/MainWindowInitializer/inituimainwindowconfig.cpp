#include "inituimainwindowconfig.h"
#include "Ui/CoreAdapter/ccserialportui_initialsources.h"
#include "Ui/MainWindow/mainwindow.h"
#include "ui_mainwindow.h"

namespace {
void configComboBox(ComboBoxUiInitializerAdapter& adapter, QComboBox* box,
                    const ComboBoxUiInitializerSource& source) {
    adapter.setComboBox(box);
    adapter.setSourses(&source);
}
}  // namespace

void InitUiMainWindowConfig::configSerialSelections(
    MEMORY_PASS_ONLY MainWindow* window) {
    ComboBoxUiInitializerAdapter  adapter;
    BaudRateComboBoxSources       baud;
    DataBitsComboBoxSources       databits;
    StopBitsComboBoxSources       stopBits;
    ParityComboBoxSources         parity;
    AvailablePortsComboBoxSources availPorts;
    configComboBox(adapter, window->ui->baud_comboBox, baud);
    configComboBox(adapter, window->ui->databits_comboBox, databits);
    configComboBox(adapter, window->ui->parify_comboBox, parity);
    configComboBox(adapter, window->ui->stopbit_comboBox, stopBits);
    configComboBox(adapter, window->ui->com_comboBox, availPorts);
    doDefaultSettings(window);
}

void InitUiMainWindowConfig::doDefaultSettings(
    MEMORY_PASS_ONLY MainWindow* window) {
    window->ui->databits_comboBox->setCurrentText(
        ConfigureConvertor::DataBitsConvertor::convert(
            QSerialPort::DataBits::Data8));
    window->ui->baud_comboBox->setCurrentText(
        ConfigureConvertor::BaudRateConvertor::convert(
            QSerialPort::BaudRate::Baud115200));
}
