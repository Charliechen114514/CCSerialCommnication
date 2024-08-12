#ifndef CCSERAILUISETTINGSACTION_H
#define CCSERAILUISETTINGSACTION_H

#include <QAction>
#include "Ui/StyleSheetsHandler/stylesheetshandler.h"
enum class RoleActions {
    Receiver_Font,
    Receiver_Color,
    Sender_Font,
    Sender_Color
};

class CCSerailUiSettingsAction : public QAction {
    Q_OBJECT
public:
    explicit CCSerailUiSettingsAction(RoleActions r, QObject *parent = nullptr);
signals:
    void tellRole(RoleActions r);

private:
    void _emitRole() {
        emit tellRole(m_r);
    }
    RoleActions m_r;
};

class CCSerialUiThemeSettings : public QAction {
    Q_OBJECT
public:
    explicit CCSerialUiThemeSettings(
        StyleSheetsHandler::ThemesDefaultPool::Selections s,
        QObject                                          *parent = nullptr);
signals:
    void tellRole(StyleSheetsHandler::ThemesDefaultPool::Selections s);

private:
    void _emitRole() {
        emit tellRole(m_r);
    }
    StyleSheetsHandler::ThemesDefaultPool::Selections m_r;
};

#endif  // CCSERAILUISETTINGSACTION_H
