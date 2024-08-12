#include "ccserialportui_initialsources.h"
#include "CCSerailPortConfigures/ccserailportconfigures.h"
#include "CCSerialPort_Core/ccserialport_core.h"
#define SOURCES(X, USING_ADAPTER)                     \
    QStringList X##ComboBoxSources::sources() const { \
        return USING_ADAPTER::labels();               \
    }

SOURCES(BaudRate, ConfigureConvertor::BaudRateConvertor)
SOURCES(StopBits, ConfigureConvertor::StopBitsConvertor)
SOURCES(Parity, ConfigureConvertor::ParityConvertor)
SOURCES(DataBits, ConfigureConvertor::DataBitsConvertor)
#undef SOURCES

QStringList AvailablePortsComboBoxSources::sources() const {
    return CCSerialPort_Core::availPortsName();
}
