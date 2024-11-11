#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QColor>

#include "../utils/parameterhandler.h"

#include "src/enums.h"

#include "src/api/internal/serverInfo.h"
#include "src/api/internal/clientAuthorization.h"

class Client;

class EventDispatcher : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool serverConnected READ serverConnected WRITE setServerConnected NOTIFY serverConnectedChanged FINAL)

    Q_PROPERTY(int userAuthorization READ userAuthorization WRITE setUserAuthorization NOTIFY userAuthorizationChanged FINAL)
    Q_PROPERTY(int userRegistration READ userRegistration WRITE setUserRegistration NOTIFY userRegistrationChanged FINAL)
    Q_PROPERTY(int userRegistrationStep READ userRegistrationStep WRITE setUserRegistrationStep NOTIFY userRegistrationStepChanged FINAL)

    Q_PROPERTY(QString serverMessage READ serverMessage WRITE setServerMessage NOTIFY serverMessageChanged FINAL)
    Q_PROPERTY(QColor serverMessageColor READ serverMessageColor WRITE setServerMessageColor NOTIFY serverMessageColorChanged FINAL)

public:
    explicit EventDispatcher(QObject *parent = nullptr);

    void registerContext(QQmlApplicationEngine& engine);
    void setClient(std::shared_ptr<Client>& client);


    // *** Command handler ***

    void commandHandler(const quint64 commandId, const QVariantMap &parameters);


    // *** UI function ***

    Q_INVOKABLE void sendSignUpRequest(const QString& phone, const QString pin);
    Q_INVOKABLE void sendLogInRequest(const QString &phone, const QString pin);


    // *** Client function ***

    void connection(const QVariantMap& parameters);
    void loginResponseHandler(const QVariantMap& parameters);


    // *** Others ***

    bool serverConnected() const;
    void setServerConnected(bool newServerConnected);

    int userAuthorization() const;
    void setUserAuthorization(int newUserAuthorization);

    QString serverMessage() const;
    void setServerMessage(const QString &newServerMessage);

    QColor serverMessageColor() const;
    void setServerMessageColor(const QColor &newServerMessageColor);

    int userRegistration() const;
    void setUserRegistration(int newUserRegistration);

    int userRegistrationStep() const;
    void setUserRegistrationStep(int newUserRegistrationStep);

signals:
    void serverConnectedChanged();
    void userAuthorizationChanged();
    void serverMessageChanged();
    void serverMessageColorChanged();
    void userRegistrationChanged();
    void userRegistrationStepChanged();

    // *** Transfer signals ***

    void command(const quint64 commandId, const QVariantMap& parameters);

private:
    bool _serverConnected = false;
    int _userAuthorization = 0;

    QString _serverMessage = "";
    QColor _serverMessageColor = QColor(0xff, 0xff, 0xff);
    int _userRegistration = 0;
    int _userRegistrationStep = 0;

    QHash<quint64, void*> _handler;

    std::shared_ptr<Client> _client;

    QMap<quint64, std::function<void(const QVariantMap&)>> _functionHandler;
};

#endif // EVENTDISPATCHER_H
