#include "client.h"

Client::Client(QObject *parent)
    : QObject{parent}
{
    using namespace std::placeholders;

    _functionHandler.insert(server::response::authorization::login::id, std::bind(&Client::loginResponseHandler, this, _1));

    _functionHandler.insert(app::request::authorization::signup::id, std::bind(&Client::signup, this, _1));
    _functionHandler.insert(app::request::authorization::login::id, std::bind(&Client::login, this, _1));
}

void Client::start()
{
    qDebug() << "Client start";

    _socket = std::make_unique<QTcpSocket>();

    QObject::connect(_socket.get(), &QTcpSocket::readyRead, this, &Client::readyRead);
    QObject::connect(_socket.get(), &QTcpSocket::connected, this, &Client::connected);
    QObject::connect(_socket.get(), &QTcpSocket::disconnected, this, &Client::disconnected);
    QObject::connect(_tryConnectTimer.get(), &QTimer::timeout, this, &Client::tryConnect);

    _tryConnectTimer->setInterval(500);
    _tryConnectTimer->start();
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

    qDebug() << "Command id:" << package.id;

    commandHandler(package.id, package.data);
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

void Client::disconnected()
{
    qDebug() << "Disconnected!";

    QVariantMap parameters;
    parameters[app::connection::connected] = false;
    emit command(app::connection::id, parameters);

    _tryConnectTimer->start();
}
void Client::connected()
{
    qDebug() << "Connected!";

    QVariantMap parameters;
    parameters[app::connection::connected] = true;
    emit command(app::connection::id, parameters);

    _tryConnectTimer->stop();
}
void Client::tryConnect()
{
    qDebug() << "Try connect...";

    _socket->connectToHost(_ip, _port);
    _socket->waitForConnected(500);
}

void Client::loginResponseHandler(const QVariantMap& parameters){
    qDebug() << parameters;

    ParameterHandler ph(parameters);

    int errorCode;
    std::optional<QString> errorMessage;

    if(!ph.handle(errorCode, server::response::authorization::login::code)) return;
    ph.handle<ParameterHandler::Optional>(errorMessage, server::response::authorization::login::message);

    QVariantMap uiParameters;

    if(errorCode == login::error){
        uiParameters[app::response::authorization::login::code] = errorCode;
        uiParameters[app::response::authorization::login::message] = "Inavlid login or password";
    }

    emit command(app::response::authorization::login::id, uiParameters);
}

void Client::signup(const QVariantMap& parameters)
{
    ParameterHandler ph(parameters);

    qint64 phoneNumber;
    qint16 pinCode;

    if(!ph.handle(phoneNumber, server::request::authorization::signup::phone)) return;
    if(!ph.handle(pinCode, server::request::authorization::signup::pin)) return;

    QVariantMap data;
    data[server::request::authorization::signup::phone] = phoneNumber;
    data[server::request::authorization::signup::pin] = pinCode;

    send(server::request::authorization::signup::id, data);
}
void Client::login(const QVariantMap& parameters){
    ParameterHandler ph(parameters);

    qint64 phoneNumber;
    qint16 pinCode;

    if(!ph.handle(phoneNumber, app::request::authorization::login::phone)) return;
    if(!ph.handle(pinCode, app::request::authorization::login::pin)) return;

    QVariantMap data;
    data[server::request::authorization::login::phone] = phoneNumber;
    data[server::request::authorization::login::pin] = pinCode;

    send(server::request::authorization::login::id, data);
}
