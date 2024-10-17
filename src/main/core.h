#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "src/client/client.h"
#include "src/main/eventdispatcher.h"

class Core : public QObject
{
    Q_OBJECT

public:
    explicit Core(QObject *parent = nullptr);

    void registerContext(QQmlApplicationEngine& engine);
    void start();

signals:

private:
    std::unique_ptr<QThread> _clientThread;
    std::shared_ptr<Client> _client;

    EventDispatcher _eventDispatcher;

    void setConnections();
};

#endif // CORE_H
