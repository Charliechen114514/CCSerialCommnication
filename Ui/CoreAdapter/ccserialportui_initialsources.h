#ifndef CCSERIALPORTUI_INITIALSOURCES_H
#define CCSERIALPORTUI_INITIALSOURCES_H
#include "uiinitializeradapter.h"

#define ANNOUCE_DEFAULT(X)                                          \
    class X##ComboBoxSources : public ComboBoxUiInitializerSource { \
    public:                                                         \
        QStringList sources() const override;                       \
    };

ANNOUCE_DEFAULT(BaudRate)
ANNOUCE_DEFAULT(StopBits)
ANNOUCE_DEFAULT(Parity)
ANNOUCE_DEFAULT(DataBits)
ANNOUCE_DEFAULT(AvailablePorts)
#undef ANNOUCE_DEFAULT

#endif  // CCSERIALPORTUI_INITIALSOURCES_H
