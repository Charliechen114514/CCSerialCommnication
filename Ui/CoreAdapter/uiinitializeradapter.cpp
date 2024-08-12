#include "uiinitializeradapter.h"
#include <QComboBox>
void ComboBoxUiInitializerAdapter::setSourses(
    const UiInitializerSource* sources) {
    auto src = dynamic_cast<const ComboBoxUiInitializerSource*>(sources);
    if (!src || !core_box) {
        return;
    }
    core_box->clear();
    core_box->addItems(src->sources());
}
