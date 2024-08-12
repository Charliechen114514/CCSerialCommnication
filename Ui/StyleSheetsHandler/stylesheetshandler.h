#ifndef STYLESHEETSHANDLER_H
#define STYLESHEETSHANDLER_H
#include "CCSerialPort_Global.h"
class QWidget;
class StyleSheetsHandler {
public:
    StyleSheetsHandler() = default;
    Q_DISABLE_COPY(StyleSheetsHandler);

    struct ThemesDefaultPool {
        enum class Selections {
            NONE,
            DARK,
            LITE,
            OSX_DARK,
            OSX_LITE,
            LIGHT_LIGHT,
            LIGHT_DARK,
            MAX
        };
        static constexpr const char*
            TEXT_NAME_LABEL[static_cast<int>(Selections::MAX)]{
                "无主题",   "Dark",        "Lite",      "OSX_DARK",
                "OSX_LITE", "LIGHT_LIGHT", "LIGHT_DARK"};
        DATA_HEAP_STR DARK     = ":/qss/Resources/mumble-theme/Dark.qss";
        DATA_HEAP_STR LITE     = ":/qss/Resources/mumble-theme/Lite.qss";
        DATA_HEAP_STR OSX_DARK = ":/qss/Resources/mumble-theme/OSX Dark.qss";
        DATA_HEAP_STR OSX_LITE = ":/qss/Resources/mumble-theme/OSX Lite.qss";
        DATA_HEAP_STR LIGHT_LIGHT =
            ":/qss/Resources/light_themes/light/lightstyle.qss";
        DATA_HEAP_STR LIGHT_DARK =
            ":/qss/Resources/light_themes/dark/darkstyle.qss";
    };

    void loadStyleSheets(QWidget* widget, QString qssPath);
    void loadStyleSheets(QWidget* widget, ThemesDefaultPool::Selections s);
};

#endif  // STYLESHEETSHANDLER_H
