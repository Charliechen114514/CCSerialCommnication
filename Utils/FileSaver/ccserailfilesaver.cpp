#include "ccserailfilesaver.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QWidget>

namespace {
QString DESKTOP =
    QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
}

QString CCSerailFileSaver::getSavePlace(QWidget* parent) {
    return QFileDialog::getSaveFileName(parent, "保存为", DESKTOP, "(*.txt)");
}

bool CCSerailFileSaver::save(const QString& buffers, const QString& atWhere) {
    QFile file(atWhere);
    if (!file.open(QIODevice::ReadWrite)) {
        return false;
    }

    return file.write(buffers.toStdString().c_str());
}
