#ifndef CCSERIALPORT_GLOBAL_H
#define CCSERIALPORT_GLOBAL_H
#include <QMap>
#include <QString>
#include <QtClassHelperMacros>
#include <memory>

#define MEMORY_HOLD_BY_OBJ_TREE
#define MEMORY_HOLD_BY_SMT_PTR
#define MEMORY_PASS_ONLY

#define BIND_UI_WIDGET inline

#define DATA_HEAP     static constexpr
#define DATA_HEAP_STR DATA_HEAP const char*

struct INIT_PARAMS {
    static constexpr short       TIMER_SCAN_AVAILABLE_COM = 1000;
    static constexpr short       INIT_PERIODLY_SEND       = 1000;
    static constexpr short       MIN_SEND_LIMIT           = 10;
    static constexpr const char* WINDOW_TITLE             = "CCSerial Window";
};

struct ABOUT_PARAM {};

#endif  // CCSERIALPORT_GLOBAL_H
