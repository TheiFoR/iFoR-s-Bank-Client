#include "core.h"

Core::Core(QObject *parent)
    : QObject{parent}
{
}

void Core::registerContext(QQmlApplicationEngine &engine)
{
    _eventDispatcher.registerContext(engine);
}

void Core::start()
{
    qDebug() << "Core started";

    _clientThread = std::make_unique<QThread>();
    _client = std::make_shared<Client>();

    setConnections();

    QObject::connect(_clientThread.get(), &QThread::started, _client.get(), &Client::start);

    _client->moveToThread(_clientThread.get());
    _clientThread->start();
}

void Core::setConnections()
{
    QObject::connect(&_eventDispatcher, &EventDispatcher::command, _client.get(), &Client::commandHandler, Qt::QueuedConnection);
    QObject::connect(_client.get(), &Client::command, &_eventDispatcher, &EventDispatcher::commandHandler, Qt::QueuedConnection);
}
