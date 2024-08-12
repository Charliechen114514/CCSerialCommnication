#include "ccserailportconfigures.h"

CCSerailPortConfigures PortConfiguresFactory::create(
    MEMORY_PASS_ONLY QSerialPort* port) {
    return {static_cast<QSerialPort::BaudRate>(port->baudRate()),
            port->dataBits(), port->flowControl(), port->parity(),
            port->stopBits()};
}

void CCSerailPortConfigures::configPort(
    MEMORY_PASS_ONLY QSerialPort* port) const {
    port->setBaudRate(baudRate);
    port->setDataBits(dataBits);
    port->setFlowControl(flowControl);
    port->setParity(parity);
    port->setStopBits(stopBits);
}

// Configures
namespace {
static constexpr QPair<const char*, QSerialPort::BaudRate> BAUD_GROUP[] = {
    {"1200", QSerialPort::BaudRate::Baud1200},
    {"2400", QSerialPort::BaudRate::Baud2400},
    {"4800", QSerialPort::BaudRate::Baud4800},
    {"9600", QSerialPort::BaudRate::Baud9600},
    {"19200", QSerialPort::BaudRate::Baud19200},
    {"38400", QSerialPort::BaudRate::Baud38400},
    {"57600", QSerialPort::BaudRate::Baud57600},
    {"115200", QSerialPort::BaudRate::Baud115200}};

static constexpr QPair<const char*, QSerialPort::DataBits> DATABITS_GROUP[]{
    {"5", QSerialPort::DataBits::Data5},
    {"6", QSerialPort::DataBits::Data6},
    {"7", QSerialPort::DataBits::Data7},
    {"8", QSerialPort::DataBits::Data8}};

static constexpr QPair<const char*, QSerialPort::StopBits> STOPBITS_GROUP[]{
    {"1bit停止位", QSerialPort::StopBits::OneStop},
    {"1.5bit停止位", QSerialPort::StopBits::OneAndHalfStop},
    {"2bit停止位", QSerialPort::StopBits::TwoStop}};

static constexpr QPair<const char*, QSerialPort::Parity> PARITY_GROUP[]{
    {"无校验位", QSerialPort::Parity::NoParity},
    {"奇校验位", QSerialPort::Parity::OddParity},
    {"偶校验位", QSerialPort::Parity::EvenParity},
    {"标记校验位", QSerialPort::Parity::MarkParity},
    {"空格校验位", QSerialPort::Parity::SpaceParity}};

template <typename Types, int SIZE>
static constexpr const char* search(
    const QPair<const char*, Types> (&map)[SIZE], Types t) {
    for (const auto& each : map) {
        if (t == each.second) return each.first;
    }
    return "";
}

template <typename Types, int SIZE>
static constexpr Types search(const QPair<const char*, Types> (&map)[SIZE],
                              const char* t) {
    for (const auto& each : map) {
        if (strcmp(t, each.first) == 0) return each.second;
    }
    return map[0].second;
}

template <typename Types, int SIZE>
static QStringList getAllLabel(const QPair<const char*, Types> (&map)[SIZE]) {
    QStringList l;
    for (const auto& each : map) {
        l << each.first;
    }
    return l;
}
}  // namespace

#define CONVERT_TO_STR(X, Types, Groups)                         \
    QString ConfigureConvertor::X##Convertor::convert(Types t) { \
        return search<Types>(Groups, t);                         \
    }

#define CONVERT_TO_TYPE(X, Types, Groups)                            \
    Types ConfigureConvertor::X##Convertor::convert(const char* t) { \
        return search<Types>(Groups, t);                             \
    }

#define CONVERT_IMPL(X, Types, Groups) \
    CONVERT_TO_STR(X, Types, Groups)   \
    CONVERT_TO_TYPE(X, Types, Groups)

CONVERT_IMPL(BaudRate, QSerialPort::BaudRate, BAUD_GROUP);
CONVERT_IMPL(DataBits, QSerialPort::DataBits, DATABITS_GROUP);
CONVERT_IMPL(StopBits, QSerialPort::StopBits, STOPBITS_GROUP);
CONVERT_IMPL(Parity, QSerialPort::Parity, PARITY_GROUP);

#undef CONVERT_IMPL
#undef CONVERT_TO_TYPE
#undef CONVERT_TO_STR

#define LABELS(X, Types, Groups)                             \
    QStringList ConfigureConvertor::X##Convertor::labels() { \
        return getAllLabel<Types>(Groups);                   \
    }

LABELS(BaudRate, QSerialPort::BaudRate, BAUD_GROUP);
LABELS(DataBits, QSerialPort::DataBits, DATABITS_GROUP);
LABELS(StopBits, QSerialPort::StopBits, STOPBITS_GROUP);
LABELS(Parity, QSerialPort::Parity, PARITY_GROUP);

#undef LABELS
