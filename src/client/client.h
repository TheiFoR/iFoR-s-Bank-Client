#ifndef CLIENT_H
#define CLIENT_H

#include "qeventloop.h"
#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QtLogging>
#include <QEventLoop>

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
    QHostAddress _ip = QHostAddress("127.0.0.1");
    quint16 _port = 1310;

    std::unique_ptr<QTcpSocket> _socket;
    std::unique_ptr<QEventLoop> _loop;
    QMap<quint64, std::function<void(const QVariantMap&)>> _functionHandler;

    QDataStream _inputStream;

    void send(quint64 commandId, const QVariantMap& data);

    QByteArray read(int msecs = 10'000);
    quint8 readUInt8(int msecs = 10'000);
    quint8 toUInt8(const QByteArray& data);

    void signup(const QVariantMap& parameters);

    template<typename T>
    QByteArray getPrepareBytes(const QString& name, T& value, qint16 size = -1);

    void login(const QVariantMap &parameters);
};

#endif // CLIENT_H
