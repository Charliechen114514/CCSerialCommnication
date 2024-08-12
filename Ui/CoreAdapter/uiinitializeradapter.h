#ifndef UIINITIALIZERADAPTER_H
#define UIINITIALIZERADAPTER_H
#include "CCSerialPort_Global.h"

class UiInitializerSource;
class UiInitializerAdapter {
public:
    UiInitializerAdapter()                                      = default;
    virtual ~UiInitializerAdapter()                             = default;
    virtual void setSourses(const UiInitializerSource* sources) = 0;
};

class UiInitializerSource {
public:
    UiInitializerSource()               = default;
    virtual ~UiInitializerSource()      = default;
    virtual QStringList sources() const = 0;
};

class QComboBox;

class ComboBoxUiInitializerSource : public UiInitializerSource {
public:
    ComboBoxUiInitializerSource()          = default;
    virtual ~ComboBoxUiInitializerSource() = default;
    virtual QStringList sources() const    = 0;
};

class ComboBoxUiInitializerAdapter : public UiInitializerAdapter {
public:
    ComboBoxUiInitializerAdapter(MEMORY_PASS_ONLY QComboBox* box)
        : core_box(box) {
    }
    ComboBoxUiInitializerAdapter() = default;
    Q_DISABLE_COPY(ComboBoxUiInitializerAdapter);
    void setComboBox(MEMORY_PASS_ONLY QComboBox* box) {
        core_box = box;
    }
    virtual void setSourses(const UiInitializerSource* sources) override;

private:
    QComboBox* core_box{nullptr};
};

#endif  // UIINITIALIZERADAPTER_H
