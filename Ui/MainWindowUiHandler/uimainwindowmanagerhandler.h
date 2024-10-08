#ifndef UIMAINWINDOWMANAGERHANDLER_H
#define UIMAINWINDOWMANAGERHANDLER_H
#include "CCSerailPortConfigures/ccserailportconfigures.h"
#include "CCSerialPort_Global.h"
#include "Ui/CommunicationDecorations/communicationdecorations.h"
#include "Ui/MenuSettingsAction/ccserailuisettingsaction.h"
#include "Ui/StatusBarWidget/statusbarwidget.h"
class MainWindow;

class UiMainWindowManagerHandler : public QObject {
    Q_OBJECT
public:
    enum class Status { ON_COMMUNICATIONS, OFF_COMMUNICATIONS };

    UiMainWindowManagerHandler(MainWindow* window, QObject* parent = nullptr)
        : QObject{parent}, window(window) {};
    UiMainWindowManagerHandler() = delete;
    Q_DISABLE_COPY(UiMainWindowManagerHandler);
    void initMainWindowUi();
    void freshComInfo();
    void appendGiving(const QString& text);
    void appendReceiving(const QString& text);
    void updateStatusLabel(QVariant infos, StatusBarWidget::StatusBarRole r);
    void clearBrowser(CommunicationDecorations::CleanMethod m);
    void toPrevHist();
    void toNextHist();
    void doSetAbleClear(bool clearAble);
    void setStatus(Status s) {
        status = s;
        doAccordingToStatus();
    }
    void   setHexMode();
    Status getStatus() const {
        return status;
    }
    QString getCurrent() const;
    QString getWhole() const;
    bool    useHex() const;

    CCSerailPortConfigures getConfigureFromUi() const;
    void                   handleSettings(RoleActions r);
    void handleThemes(StyleSheetsHandler::ThemesDefaultPool::Selections s);

signals:
    void tellStopScan();

private:
    MEMORY_PASS_ONLY MainWindow* window{nullptr};
    void                         doAccordingToStatus();
    void                         doOnCommun();
    void                         doOffCommun();

    void initMenu();
    void initUiRevSendSettingsMenu();
    void initThemeSettings();
    void loadStyleSheets();
    void helpConfigMenu(QMenu* menu, RoleActions r, QString text);
    void helpConfigThemeMenu(
        QMenu* menu, StyleSheetsHandler::ThemesDefaultPool::Selections s,
        QString text);
    Status status = Status::OFF_COMMUNICATIONS;
    std::unique_ptr<CommunicationDecorations> browser_decorator;
    std::unique_ptr<StatusBarWidget>          status_bar_widget;
};

#endif  // UIMAINWINDOWMANAGERHANDLER_H
