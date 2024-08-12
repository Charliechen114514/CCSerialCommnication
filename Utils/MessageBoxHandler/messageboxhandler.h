#ifndef MESSAGEBOXHANDLER_H
#define MESSAGEBOXHANDLER_H
#include "CCSerialPort_Global.h"
class QWidget;

class MessageBoxHandler {
public:
    struct ErrorInform {
        static void tellError(QString title, QString captions, QWidget* parent);
    };

    struct InfoInform {
        static bool inform(QString title, QString captions, QWidget* parent);
    };

    struct AskForQuery {
        static bool query(QString title, QString captions, QWidget* parent);
    };

    struct About {
        static void showAbout(QWidget* parent, QString displays);
    };
};

#endif  // MESSAGEBOXHANDLER_H
