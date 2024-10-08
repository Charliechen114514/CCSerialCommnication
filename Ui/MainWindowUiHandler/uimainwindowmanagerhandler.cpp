#include "uimainwindowmanagerhandler.h"
#include <QColorDialog>
#include <QFontDialog>
#include "MainWindowInitializer/inituimainwindowconfig.h"
#include "Ui/CoreAdapter/ccserialportui_initialsources.h"
#include "Ui/CoreAdapter/uiinitializeradapter.h"
#include "Ui/MainWindow/mainwindow.h"
#include "Ui/StyleSheetsHandler/stylesheetshandler.h"
#include "ui_mainwindow.h"
void UiMainWindowManagerHandler::initMainWindowUi() {
    window->ui->setupUi(window);
    window->setWindowTitle(INIT_PARAMS::WINDOW_TITLE);
    InitUiMainWindowConfig::configSerialSelections(window);
    browser_decorator = std::make_unique<CommunicationDecorations>(
        window->ui->receiving_window);
    status_bar_widget = std::make_unique<StatusBarWidget>(window);
    status_bar_widget->setReceivingCounts(0);
    status_bar_widget->setSendCounts(0);
    window->ui->statusbar->addPermanentWidget(status_bar_widget.get());

    connect(window->ui->com_comboBox, &QComboBox::activated, this,
            &UiMainWindowManagerHandler::tellStopScan);

    doOffCommun();
    initMenu();
    loadStyleSheets();
}

void UiMainWindowManagerHandler::setHexMode() {
    browser_decorator->setshellHex(window->ui->checkBox_showHex->isChecked());
    browser_decorator->refreshStores(
        browser_decorator->cleanHelper.isFin()
            ? browser_decorator->finLastStage()
            : browser_decorator->cleanHelper.current_focusing());
}

void UiMainWindowManagerHandler::freshComInfo() {
    ComboBoxUiInitializerAdapter  adapter;
    AvailablePortsComboBoxSources sources;
    adapter.setComboBox(window->ui->com_comboBox);
    adapter.setSourses(&sources);
}

void UiMainWindowManagerHandler::doAccordingToStatus() {
    switch (status) {
        case Status::ON_COMMUNICATIONS:
            doOnCommun();
            break;
        case Status::OFF_COMMUNICATIONS:
            doOffCommun();
            break;
    }
}

void UiMainWindowManagerHandler::clearBrowser(
    CommunicationDecorations::CleanMethod m) {
    browser_decorator->clearBrowser(m);
}

void UiMainWindowManagerHandler::updateStatusLabel(
    QVariant infos, StatusBarWidget::StatusBarRole r) {
    switch (r) {
        case StatusBarWidget::StatusBarRole::RECEIVE: {
            int receive = infos.toInt();
            status_bar_widget->setReceivingCounts(receive);
        } break;
        case StatusBarWidget::StatusBarRole::SEND: {
            int send = infos.toInt();
            status_bar_widget->setSendCounts(send);
        } break;
        case StatusBarWidget::StatusBarRole::ErrorOccur:
            QString res = infos.toString();
            window->ui->statusbar->showMessage(res);
            break;
    }
}

void UiMainWindowManagerHandler::appendGiving(const QString& text) {
    browser_decorator->appendSending(text);
}
void UiMainWindowManagerHandler::appendReceiving(const QString& text) {
    browser_decorator->appendReceivings(text);
}

// 设置正在通信的状态
void UiMainWindowManagerHandler::doOnCommun() {
    window->ui->com_comboBox->setEnabled(false);
    window->ui->baud_comboBox->setEnabled(false);
    window->ui->parify_comboBox->setEnabled(false);
    window->ui->databits_comboBox->setEnabled(false);
    window->ui->stopbit_comboBox->setEnabled(false);
    window->ui->btn_start_serial->setText("关闭串口");
    window->ui->btn_send_data->setEnabled(true);
    window->ui->statusbar->showMessage("串口开启！");
    window->ui->btn_start_serial->setIcon(
        QIcon(":/icons/Resources/application_icons/OnCommunications.png"));
}

// 设置关闭通信的状态
void UiMainWindowManagerHandler::doOffCommun() {
    window->ui->com_comboBox->setEnabled(true);
    window->ui->baud_comboBox->setEnabled(true);
    window->ui->parify_comboBox->setEnabled(true);
    window->ui->databits_comboBox->setEnabled(true);
    window->ui->stopbit_comboBox->setEnabled(true);
    window->ui->btn_start_serial->setText("打开串口");
    window->ui->btn_send_data->setEnabled(false);
    window->ui->statusbar->showMessage("串口关闭！");
    window->ui->btn_start_serial->setIcon(
        QIcon(":/icons/Resources/application_icons/OffCommunications.png"));
}

void UiMainWindowManagerHandler::toPrevHist() {
    if (browser_decorator->cleanHelper.isNoCleanHistory()) return;

    browser_decorator->cleanHelper.operateValidPointer(
        CommunicationDecorations::CleanHistoryHelper::Operation::TO_PREV);

    QPair<int, int> get;
    if (window->ui->receiving_window->toPlainText().isEmpty()) {
        get = browser_decorator->cleanHelper.lastHistory();
    } else {
        get = browser_decorator->cleanHelper.current_focusing();
    }
    browser_decorator->refreshStores(get);
    window->ui->btn_send_data->setEnabled(false);
    window->ui->btn_clear_output->setEnabled(false);
}

void UiMainWindowManagerHandler::doSetAbleClear(bool st) {
    window->ui->btn_clear_output->setEnabled(st);
    window->ui->btn_toNext->setEnabled(st);
    window->ui->btn_toPrev->setEnabled(st);
    window->ui->btn_clearRestore->setEnabled(st);
}

void UiMainWindowManagerHandler::toNextHist() {
    if (browser_decorator->cleanHelper.isNoCleanHistory()) return;

    browser_decorator->cleanHelper.operateValidPointer(
        CommunicationDecorations::CleanHistoryHelper::Operation::TO_NEXT);

    QPair<int, int> res;
    if (browser_decorator->cleanHelper.isFin()) {
        // is the same last
        res = browser_decorator->finLastStage();
        window->ui->btn_send_data->setEnabled(true);
        window->ui->btn_clear_output->setEnabled(true);
    } else {
        res = browser_decorator->cleanHelper.current_focusing();
    }

    browser_decorator->refreshStores(res);
}

#define GET_FROM_COMBOBOX(var, comboBoxName, X)           \
    auto var = ConfigureConvertor::X##Convertor::convert( \
        window->ui->comboBoxName->currentText().toStdString().c_str())

CCSerailPortConfigures UiMainWindowManagerHandler::getConfigureFromUi() const {
    qDebug() << window->ui->baud_comboBox->currentText();
    GET_FROM_COMBOBOX(baud, baud_comboBox, BaudRate);
    GET_FROM_COMBOBOX(parity, parify_comboBox, Parity);
    GET_FROM_COMBOBOX(stopBits, stopbit_comboBox, StopBits);
    GET_FROM_COMBOBOX(dataBits, databits_comboBox, DataBits);

    return {baud, dataBits, QSerialPort::NoFlowControl, parity, stopBits};
}

void UiMainWindowManagerHandler::helpConfigMenu(QMenu* menu, RoleActions r,
                                                QString text) {
    auto actions = new CCSerailUiSettingsAction(r, menu);
    menu->addAction(actions);
    actions->setText(text);
    connect(actions, &CCSerailUiSettingsAction::tellRole, this,
            &UiMainWindowManagerHandler::handleSettings);
}

void UiMainWindowManagerHandler::helpConfigThemeMenu(
    QMenu* menu, StyleSheetsHandler::ThemesDefaultPool::Selections s,
    QString text) {
    auto actions = new CCSerialUiThemeSettings(s, menu);
    menu->addAction(actions);
    actions->setText(text);
    connect(actions, &CCSerialUiThemeSettings::tellRole, this,
            &UiMainWindowManagerHandler::handleThemes);
}

void UiMainWindowManagerHandler::initMenu() {
    initUiRevSendSettingsMenu();
    initThemeSettings();
}

void UiMainWindowManagerHandler::initUiRevSendSettingsMenu() {
    QMenu* receiving_menu = new QMenu(window->ui->menu_settings);
    window->ui->menu_settings->addMenu(receiving_menu);
    receiving_menu->setTitle("设置接受方...");
    helpConfigMenu(receiving_menu, RoleActions::Receiver_Color,
                   "接收方字体颜色");
    helpConfigMenu(receiving_menu, RoleActions::Receiver_Font, "接收方字体");
    QMenu* sender_menu = new QMenu(window->ui->menu_settings);
    sender_menu->setTitle("设置发送方...");
    window->ui->menu_settings->addMenu(sender_menu);
    helpConfigMenu(sender_menu, RoleActions::Sender_Font, "发送方字体");
    helpConfigMenu(sender_menu, RoleActions::Sender_Color, "发送方字体颜色");
}

void UiMainWindowManagerHandler::initThemeSettings() {
    for (int i = 0;
         i < static_cast<int>(
                 StyleSheetsHandler::ThemesDefaultPool::Selections::MAX);
         i++) {
        helpConfigThemeMenu(
            window->ui->menu_themes,
            static_cast<StyleSheetsHandler::ThemesDefaultPool::Selections>(i),
            StyleSheetsHandler::ThemesDefaultPool::TEXT_NAME_LABEL[i]);
    }
}

void UiMainWindowManagerHandler::loadStyleSheets() {
    StyleSheetsHandler handler;
    handler.loadStyleSheets(window,
                            StyleSheetsHandler::ThemesDefaultPool::OSX_LITE);
}

void UiMainWindowManagerHandler::handleThemes(
    StyleSheetsHandler::ThemesDefaultPool::Selections r) {
    StyleSheetsHandler handler;
    handler.loadStyleSheets(window, r);
}

void UiMainWindowManagerHandler::handleSettings(RoleActions r) {
    QColor c;
    QFont  f;
    auto   role = CommunicationDecorations::TextBrowserStyleControl::
        CharFormatRole::Receiver;

    switch (r) {
        case RoleActions::Receiver_Font: {
            bool ok = false;
            f       = QFontDialog::getFont(&ok);
            if (!ok) {
                return;
            }
            c = browser_decorator->controller.receiverCharFormat.foreground()
                    .color();
            role = CommunicationDecorations::TextBrowserStyleControl::
                CharFormatRole::Receiver;
        } break;
        case RoleActions::Receiver_Color: {
            c = QColorDialog::getColor();
            if (!c.isValid()) {
                return;
            }
            f    = browser_decorator->controller.receiverCharFormat.font();
            role = CommunicationDecorations::TextBrowserStyleControl::
                CharFormatRole::Receiver;
        } break;
        case RoleActions::Sender_Font: {
            bool ok = false;
            f       = QFontDialog::getFont(&ok);
            if (!ok) {
                return;
            }
            c = browser_decorator->controller.senderCharFormat.foreground()
                    .color();
            role = CommunicationDecorations::TextBrowserStyleControl::
                CharFormatRole::Sender;
        } break;
        case RoleActions::Sender_Color: {
            c = QColorDialog::getColor();
            if (!c.isValid()) {
                return;
            }
            f    = browser_decorator->controller.senderCharFormat.font();
            role = CommunicationDecorations::TextBrowserStyleControl::
                CharFormatRole::Sender;
        } break;
    }

    browser_decorator->controller.setCharFormat(f, c, role);
    browser_decorator->refreshStores();
}

QString UiMainWindowManagerHandler::getCurrent() const {
    return browser_decorator->exportSavings(
        CommunicationDecorations::SavingMethod::CURRENT_FRAME);
}

QString UiMainWindowManagerHandler::getWhole() const {
    return browser_decorator->exportSavings(
        CommunicationDecorations::SavingMethod::ALL);
}

bool UiMainWindowManagerHandler::useHex() const {
    return window->ui->checkBox_showHex->isChecked();
}
