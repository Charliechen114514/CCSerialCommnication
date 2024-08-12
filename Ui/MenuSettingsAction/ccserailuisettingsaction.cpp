#include "ccserailuisettingsaction.h"

CCSerailUiSettingsAction::CCSerailUiSettingsAction(RoleActions r,
                                                   QObject    *parent)
    : QAction{parent}, m_r(r) {
    connect(this, &QAction::triggered, this,
            &CCSerailUiSettingsAction::_emitRole);
}

CCSerialUiThemeSettings::CCSerialUiThemeSettings(
    StyleSheetsHandler::ThemesDefaultPool::Selections s, QObject *parent)
    : QAction{parent}, m_r(s) {
    connect(this, &QAction::triggered, this,
            &CCSerialUiThemeSettings::_emitRole);
}
