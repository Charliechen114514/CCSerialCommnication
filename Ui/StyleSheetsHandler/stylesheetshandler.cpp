#include "stylesheetshandler.h"
#include <QDir>
#include <QFile>
#include <QWidget>
void StyleSheetsHandler::loadStyleSheets(QWidget* widget, QString qssPath) {
    QFile f(qssPath);
    f.open(QIODevice::ReadOnly);
    if (f.isOpen()) {
        QString buffers = f.readAll();
        QDir::setCurrent("./Resources");
        widget->setStyleSheet(buffers);
        QDir::setCurrent(".");
    }
}

void StyleSheetsHandler::loadStyleSheets(QWidget*                      widget,
                                         ThemesDefaultPool::Selections s) {
    switch (s) {
        case ThemesDefaultPool::Selections::DARK:
            loadStyleSheets(widget, ThemesDefaultPool::DARK);
            break;
        case ThemesDefaultPool::Selections::LITE:
            loadStyleSheets(widget, ThemesDefaultPool::LITE);
            break;
        case ThemesDefaultPool::Selections::OSX_DARK:
            loadStyleSheets(widget, ThemesDefaultPool::OSX_DARK);
            break;
        case ThemesDefaultPool::Selections::OSX_LITE:
            loadStyleSheets(widget, ThemesDefaultPool::OSX_LITE);
            break;
        case ThemesDefaultPool::Selections::MAX:
            break;
        case ThemesDefaultPool::Selections::NONE:
            widget->setStyleSheet("");
            break;
        case ThemesDefaultPool::Selections::LIGHT_LIGHT:
            loadStyleSheets(widget, ThemesDefaultPool::LIGHT_LIGHT);
            break;
        case ThemesDefaultPool::Selections::LIGHT_DARK:
            loadStyleSheets(widget, ThemesDefaultPool::LIGHT_DARK);
            break;
    }
}
