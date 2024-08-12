#include "messageboxhandler.h"
#include <QMessageBox>

void MessageBoxHandler::ErrorInform::tellError(QString title, QString captions,
                                               QWidget* parent) {
    QMessageBox::critical(parent, title, captions);
}

bool MessageBoxHandler::InfoInform::inform(QString title, QString captions,
                                           QWidget* parent) {
    return QMessageBox::StandardButton::Ok ==
           QMessageBox::information(parent, title, captions);
}

bool MessageBoxHandler::AskForQuery::query(QString title, QString captions,
                                           QWidget* parent) {
    return QMessageBox::StandardButton::Yes ==
           QMessageBox::question(parent, title, captions);
}

void MessageBoxHandler::About::showAbout(QWidget* parent, QString displays) {
    return QMessageBox::about(parent, "关于", displays);
}
