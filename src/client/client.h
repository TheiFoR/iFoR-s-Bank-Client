#ifndef CLIENT_H
#define CLIENT_H

#include "qeventloop.h"
#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QtLogging>
#include <QEventLoop>
#include <QTimer>

#include "src/settings.h"
#include "src/utils/byteparser.h"
#include "src/utils/parameterhandler.h"

#include "src/enums.h"

#include "src/api/external/serverAuthorization.h"
#include "src/api/internal/serverInfo.h"
#include "src/api/internal/clientAuthorization.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

public slots:
    void start();

    void commandHandler(const quint64 commandId, const QVariantMap& parameters);

    void readyRead();

    void disconnected();
    void connected();
    void tryConnect();

signals:
    void command(quint64 commandId, const QVariantMap& parameters = QVariantMap());

private:
    QHostAddress _ip = Settings::ip;
    quint16 _port = Settings::port;

    QMap<quint64, std::function<void(const QVariantMap &)>> _functionHandler;

    std::unique_ptr<QTcpSocket> _socket;
    std::unique_ptr<QTimer> _tryConnectTimer = std::make_unique<QTimer>(this);

    ByteParser _byteParser;



    void send(quint64 commandId, const QVariantMap &data);

    void loginResponseHandler(const QVariantMap &parameters);

    void signup(const QVariantMap &parameters);
    void login(const QVariantMap &parameters);
};

#endif // CLIENT_H
