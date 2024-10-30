#ifndef CLIENT_H
#define CLIENT_H

#include "qeventloop.h"
#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QtLogging>
#include <QEventLoop>

#include "src/settings.h"
#include "src/utils/byteparser.h"
#include "src/utils/parameterhandler.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

public slots:
    void start();

    void commandHandler(const quint64 commandId, const QVariantMap& parameters);

    void readyRead();

signals:
    void command(quint64 commandId, const QVariantMap& parameters = QVariantMap());

private:
    QHostAddress _ip = Settings::ip;
    quint16 _port = Settings::port;

    QMap<quint64, std::function<void(const QVariantMap &)>> _functionHandler;

    std::unique_ptr<QTcpSocket> _socket;

    ByteParser _byteParser;



    void send(quint64 commandId, const QVariantMap &data);
    QByteArray read(int msecs = 10'000);

    void signup(const QVariantMap &parameters);
    void login(const QVariantMap &parameters);

    template <typename T>
    QByteArray getPrepareBytes(const QString &name, T &value, qint16 size = -1);
};

#endif // CLIENT_H
