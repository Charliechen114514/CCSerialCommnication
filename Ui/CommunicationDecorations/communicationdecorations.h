#ifndef COMMUNICATIONDECORATIONS_H
#define COMMUNICATIONDECORATIONS_H
#include <CCSerialPort_Global.h>
#include <QDateTime>
#include <QTextCharFormat>
class QTextBrowser;
class CommunicationDecorations {
public:
    CommunicationDecorations() = delete;
    CommunicationDecorations(MEMORY_PASS_ONLY QTextBrowser* browser);
    Q_DISABLE_COPY(CommunicationDecorations);
    struct Restorings {
        enum class Role { Sender, Receiver } role;
        Restorings() = delete;
        Restorings(Role r, int index, QString s, QDateTime t)
            : role(r), comming_index(index), stores(s), time(t) {
        }

        int       comming_index;
        QString   stores;
        QDateTime time;
    };

    struct HexConvertor {
        static void convert(QString& string) {
            string  = string.toUtf8().toHex().toUpper();
            int len = string.size();
            while (len - 2 > 0) {
                len -= 2;
                string.insert(len, ' ');
            }
        }
    };

    struct TextBrowserStyleControl {
        TextBrowserStyleControl();
        enum class CharFormatRole { Sender, Receiver, Manager };
        struct CharFormatControllerFactory {
            static QTextCharFormat create(const QFont&  font,
                                          const QColor& color);
        };
        void            setCharFormat(const QFont& font, const QColor& color,
                                      CharFormatRole role);
        QTextCharFormat senderCharFormat;
        QTextCharFormat receiverCharFormat;
        QTextCharFormat managerCharFormat;
    } controller;

    struct TextBrowserPrefix {
        enum class PrefixRole { Sender, Receiver, Manager };
        QString wrap(const QString& text, PrefixRole role) const;
        QString wrap(const QString& text, const QDateTime& r,
                     PrefixRole role) const;
        struct PrefixPackage {
            bool    req_timeSettings = true;
            QString timeSettings() const {
                return QString(" (%1) ").arg(
                           QDateTime::currentDateTime().toString()) +
                       "\n";
            }
            QString timeSettings(const QDateTime& t) const {
                return QString(" (%1) ").arg(t.toString()) + "\n";
            }

            QString raw_prefix;
            QString prefixs() const {
                return req_timeSettings ? timeSettings() + raw_prefix
                                        : raw_prefix;
            }
            QString prefixs(const QDateTime& t) const {
                return req_timeSettings ? timeSettings(t) + raw_prefix
                                        : raw_prefix;
            }
            static constexpr const char* default_sender_prefix   = "你: \n";
            static constexpr const char* default_receiver_prefix = "对方: \n";
            static constexpr const char* default_manager_prefix  = "";
        } prefixPackage[3] = {{true, PrefixPackage::default_sender_prefix},
                              {true, PrefixPackage::default_receiver_prefix},
                              {true, PrefixPackage::default_manager_prefix}};

        static constexpr short fromRoleFindPack(PrefixRole r) noexcept {
            return static_cast<short>(r);
        }

        QString getDisplayRestorings(const Restorings& r, bool shellHex) const {
            QString res = r.stores;
            if (shellHex) HexConvertor::convert(res);
            switch (r.role) {
                case Restorings::Role::Sender:
                    return wrap(res, r.time, PrefixRole::Sender);
                case Restorings::Role::Receiver:
                    return wrap(res, r.time, PrefixRole::Receiver);
            }
            return "";
        }

    } textBrowserPrefix;

    struct CleanHistoryHelper {
    public:
        enum class Operation { TO_PREV, TO_NEXT };
        bool isNoCleanHistory() {
            return cleanStage.empty();
        }
        QPair<int, int> enCleanHist(const int& index) {
            QPair<int, int> pair = {};
            if (cleanStage.empty()) {
                pair = QPair<int, int>(0, index);
                cleanStage << pair;
                return pair;
            }
            if (index != cleanStage.last().second) {
                pair = QPair<int, int>(cleanStage.last().second + 1, index);
                cleanStage << pair;
            }
            return pair;
        }

        int operateValidPointer(Operation o) {
            switch (o) {
                case Operation::TO_PREV:
                    if (!isFin()) {
                        current_pointer_index--;
                    }
                    if (current_pointer_index <= 0) current_pointer_index = 0;
                    isFinal = false;
                    break;
                case Operation::TO_NEXT:
                    current_pointer_index++;
                    if (current_pointer_index == cleanStage.size())
                        isFinal = true;
                    if (current_pointer_index >= cleanStage.size())
                        current_pointer_index = cleanStage.size() - 1;
                    break;
            }
            return current_pointer_index;
        }
        QPair<int, int> current_focusing() const {
            if (cleanStage.empty()) return {};
            return cleanStage[current_pointer_index];
        }

        int current_focusing_index() const {
            return current_pointer_index;
        }

        QPair<int, int> last() const {
            if (cleanStage.empty()) return {};
            return cleanStage.last();
        }
        bool isFin() const {
            return isFinal;
        }

        QPair<int, int> lastHistory() {
            if (isNoCleanHistory()) return {};
            return cleanStage.last();
        }

    private:
        bool                   isFinal               = true;
        int                    current_pointer_index = 0;
        QList<QPair<int, int>> cleanStage;
    } cleanHelper;

    bool validStage(const QPair<int, int>& p) const {
        return p.first >= 0 && p.second <= restorings.size() &&
               p.first <= p.second;
    }

    QPair<int, int> finLastStage() {
        if (cleanHelper.isNoCleanHistory())
            return {0, restorings.last().comming_index};
        return {cleanHelper.last().second + 1, restorings.last().comming_index};
    }

    enum class CleanMethod { CLEAN_TEMP, CLEAN_RESTORE };

    void appendReceivings(const QString& receivings);
    void appendSending(const QString& receivings);
    void appendRecord(const QString& receivings, Restorings::Role r);
    void refreshStores();
    void refreshStores(const QPair<int, int>& stages);
    void clearBrowser(CleanMethod m);

    enum class SavingMethod { CURRENT_FRAME, ALL };

    QString exportSavings(SavingMethod m);
    void    setshellHex(const bool st) {
        shellShowHex = st;
    }

private:
    QTextBrowser* handling_browser{nullptr};
    bool          shellShowHex = false;
    void          appendSending_Raw(const QString& receivings);
    void          appendReceiving_Raw(const QString& receivings);
    void          appendSendingHist(const Restorings& r);
    void          appendReceivingHist(const Restorings& r);
    void          clearStores() {
        restorings.clear();
    }
    QList<Restorings> restorings;

    int comming_index = 0;
};

#endif  // COMMUNICATIONDECORATIONS_H
