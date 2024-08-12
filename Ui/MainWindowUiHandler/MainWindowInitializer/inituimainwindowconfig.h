#ifndef INITUIMAINWINDOWCONFIG_H
#define INITUIMAINWINDOWCONFIG_H
#include "CCSerialPort_Global.h"
class MainWindow;
class InitUiMainWindowConfig {
public:
    InitUiMainWindowConfig() = default;
    static void configSerialSelections(MEMORY_PASS_ONLY MainWindow* window);

private:
    static void doDefaultSettings(MEMORY_PASS_ONLY MainWindow* window);
};

#endif  // INITUIMAINWINDOWCONFIG_H
