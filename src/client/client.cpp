#include "client.h"

#include "src/api/external/serverAuthorization.h"
#include "src/api/internal/serverInfo.h"
#include "src/api/internal/clientAuthorization.h"

Client::Client(QObject *parent)
    : QObject{parent}
{
    using namespace std::placeholders;

    _functionHandler.insert(app::signup::id, std::bind(&Client::signup, this, _1));
    _functionHandler.insert(app::login::id, std::bind(&Client::login, this, _1));
}

void Client::start()
{
    qDebug() << "Client start";

    _socket = std::make_unique<QTcpSocket>();

    QObject::connect(_socket.get(), &QTcpSocket::readyRead, this, &Client::readyRead);

    _socket->connectToHost(_ip, _port);

    if(_socket->waitForConnected(10000)){
        qDebug() << "Connection!";
        QVariantMap parameters;
        parameters[app::connection::connected] = true;
        emit command(app::connection::id, parameters);
    }
}


void Client::commandHandler(const quint64 commandId, const QVariantMap &parameters)
{
    QMap<quint64, std::function<void(const QVariantMap&)>>::iterator iter = _functionHandler.find(commandId);
    if (iter != _functionHandler.end())
    {
        iter.value()(parameters);
    }
    else{
        qWarning() << "Unknown command id:" << commandId;
    }
}

void Client::readyRead()
{
    QByteArray data = _socket->readAll();
    Package package;

    package = _byteParser.parse(data);
    qDebug() << "Data from the server:" << package.id << package.data;
}


void Client::send(quint64 commandId, const QVariantMap& data) {
    Package package;
    package.id = commandId;
    package.data = data;

    QByteArray bytes = _byteParser.unparse(package);

    qDebug() << "Send to the server:" << data;
    qDebug() << "Send to the server raw:" << bytes;

    _socket->write(bytes);
}
QByteArray Client::read(int msecs)
{
    while(!_socket->waitForReadyRead(msecs) && _socket->isValid()){
        qWarning("Long response from the server. Waiting for a response...");
    }
    if(!_socket->isValid()){
        qCritical("Server has been closed!");
        return "";
    }
    QByteArray data = _socket->readAll();
    qDebug() << "Data from the server:" << data;
    return data;
}

void Client::signup(const QVariantMap& parameters)
{
    ParameterHandler ph(parameters);

    qint64 phoneNumber;
    qint16 pinCode;

    if(!ph.handle(phoneNumber, server::request::signup::phone)) return;
    if(!ph.handle(pinCode, server::request::signup::pin)) return;

    QVariantMap data;
    data[server::request::signup::phone] = phoneNumber;
    data[server::request::signup::pin] = pinCode;

    send(server::request::signup::id, data);
}
void Client::login(const QVariantMap& parameters){
    ParameterHandler ph(parameters);

    qint64 phoneNumber;
    qint16 pinCode;

    if(!ph.handle(phoneNumber, app::login::phone)) return;
    if(!ph.handle(pinCode, app::login::pin)) return;

    QVariantMap data;
    data[server::request::login::phone] = phoneNumber;
    data[server::request::login::pin] = pinCode;

    send(server::request::login::id, data);
}
