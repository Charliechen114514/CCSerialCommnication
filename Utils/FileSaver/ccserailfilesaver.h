#ifndef CCSERAILFILESAVER_H
#define CCSERAILFILESAVER_H
#include <QString>

class QWidget;
class CCSerailFileSaver {
public:
    CCSerailFileSaver() = default;
    static QString getSavePlace(QWidget* parent);
    static bool    save(const QString& buffers, const QString &atWhere);
};

#endif  // CCSERAILFILESAVER_H
