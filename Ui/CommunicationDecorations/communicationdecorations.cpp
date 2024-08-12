#include "communicationdecorations.h"
#include <QTextBrowser>
CommunicationDecorations::CommunicationDecorations(QTextBrowser* browser)
    : handling_browser(browser) {
}

void CommunicationDecorations::appendRecord(const QString&   receivings,
                                            Restorings::Role r) {
    restorings << Restorings(r, comming_index, receivings,
                             QDateTime::currentDateTime());
    comming_index++;
}

void CommunicationDecorations::appendReceivings(const QString& receivings) {
    appendRecord(receivings, Restorings::Role::Receiver);
    appendReceiving_Raw(receivings);
}

void CommunicationDecorations::appendSending(const QString& receivings) {
    appendRecord(receivings, Restorings::Role::Sender);
    appendSending_Raw(receivings);
}

void CommunicationDecorations::appendSending_Raw(const QString& receivings) {
    QString res = receivings;
    if (shellShowHex) HexConvertor::convert(res);
    auto             cursor = handling_browser->textCursor();
    QTextBlockFormat format;
    QString          readyDisplay =
        textBrowserPrefix.wrap(res, TextBrowserPrefix::PrefixRole::Sender);
    format.setAlignment(Qt::AlignRight);
    cursor.setCharFormat(controller.senderCharFormat);
    cursor.insertBlock(format);
    cursor.insertText(readyDisplay);
    handling_browser->moveCursor(QTextCursor::End);
}
void CommunicationDecorations::appendReceiving_Raw(const QString& receivings) {
    QString res = receivings;
    if (shellShowHex) HexConvertor::convert(res);
    auto             cursor = handling_browser->textCursor();
    QTextBlockFormat format;
    QString          readyDisplay =
        textBrowserPrefix.wrap(res, TextBrowserPrefix::PrefixRole::Receiver);
    format.setAlignment(Qt::AlignLeft);
    cursor.setCharFormat(controller.receiverCharFormat);
    cursor.insertBlock(format);
    cursor.insertText(readyDisplay);
    handling_browser->moveCursor(QTextCursor::End);
}

void CommunicationDecorations::appendSendingHist(const Restorings& r) {
    QString readyDisplay =
        textBrowserPrefix.getDisplayRestorings(r, shellShowHex);
    auto             cursor = handling_browser->textCursor();
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignRight);
    cursor.setCharFormat(controller.senderCharFormat);
    cursor.insertBlock(format);
    cursor.insertText(readyDisplay);
    handling_browser->moveCursor(QTextCursor::End);
}
void CommunicationDecorations::appendReceivingHist(const Restorings& r) {
    QString readyDisplay =
        textBrowserPrefix.getDisplayRestorings(r, shellShowHex);
    auto             cursor = handling_browser->textCursor();
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignLeft);
    cursor.setCharFormat(controller.receiverCharFormat);
    cursor.insertBlock(format);
    cursor.insertText(readyDisplay);
    handling_browser->moveCursor(QTextCursor::End);
}

QTextCharFormat CommunicationDecorations::TextBrowserStyleControl::
    CharFormatControllerFactory::create(const QFont&  font,
                                        const QColor& color) {
    QTextCharFormat f;
    f.setFont(font);
    f.setForeground(color);
    return f;
}

CommunicationDecorations::TextBrowserStyleControl::TextBrowserStyleControl() {
    QFont  defaultReceiverFont("Consola", 12);
    QColor defaultReceiverColor(Qt::blue);
    receiverCharFormat = CharFormatControllerFactory::create(
        defaultReceiverFont, defaultReceiverColor);

    QFont  defaultSenderFont("Consola", 12);
    QColor defaultSenderColor(Qt::red);
    senderCharFormat = CharFormatControllerFactory::create(defaultSenderFont,
                                                           defaultSenderColor);
}

void CommunicationDecorations::TextBrowserStyleControl::setCharFormat(
    const QFont& font, const QColor& color, CharFormatRole role) {
    QTextCharFormat result = CharFormatControllerFactory::create(font, color);
    switch (role) {
        case CharFormatRole::Sender:
            senderCharFormat = result;
            break;
        case CharFormatRole::Receiver:
            receiverCharFormat = result;
            break;
        case CharFormatRole::Manager:
            managerCharFormat = result;
            break;
    }
}

QString CommunicationDecorations::TextBrowserPrefix::wrap(
    const QString& text, PrefixRole role) const {
    return prefixPackage[fromRoleFindPack(role)].prefixs() + text;
}

QString CommunicationDecorations::TextBrowserPrefix::wrap(
    const QString& text, const QDateTime& r, PrefixRole role) const {
    return prefixPackage[fromRoleFindPack(role)].prefixs(r) + text;
}

void CommunicationDecorations::refreshStores() {
    handling_browser->clear();
    for (const auto& each : restorings) {
        switch (each.role) {
            case Restorings::Role::Sender:
                appendSendingHist(each);
                break;
            case Restorings::Role::Receiver:
                appendReceivingHist(each);
                break;
        }
    }
}

void CommunicationDecorations::refreshStores(const QPair<int, int>& stages) {
    handling_browser->clear();
    if (!validStage(stages)) return;
    for (int i = stages.first; i <= stages.second; i++) {
        auto each = restorings[i];
        switch (each.role) {
            case Restorings::Role::Sender:
                appendSendingHist(each);
                break;
            case Restorings::Role::Receiver:
                appendReceivingHist(each);
                break;
        }
    }
}

void CommunicationDecorations::clearBrowser(CleanMethod m) {
    if (restorings.empty()) return;
    switch (m) {
        case CleanMethod::CLEAN_TEMP:
            qDebug() << cleanHelper.enCleanHist(
                restorings.last().comming_index);
            handling_browser->clear();
            break;
        case CleanMethod::CLEAN_RESTORE:
            clearStores();
            handling_browser->clear();
            break;
    }
}

QString CommunicationDecorations::exportSavings(SavingMethod m) {
    switch (m) {
        case SavingMethod::CURRENT_FRAME:
            return handling_browser->toPlainText();
        case SavingMethod::ALL: {
            QString res;
            for (const auto& restore : restorings) {
                res += textBrowserPrefix.getDisplayRestorings(restore,
                                                              shellShowHex);
            }
            return res;
        }
    }
    return "";
}
