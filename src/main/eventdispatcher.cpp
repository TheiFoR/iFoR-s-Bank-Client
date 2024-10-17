#include "eventdispatcher.h"

EventDispatcher::EventDispatcher(QObject *parent)
    : QObject{parent}
{
    using namespace std::placeholders;

    _functionHandler.insert(app::connection::id, std::bind(&EventDispatcher::connection, this, _1));
}

void EventDispatcher::registerContext(QQmlApplicationEngine &engine)
{
    engine.rootContext()->setContextProperty("core", this);
}


// *** Command handler ***

void EventDispatcher::commandHandler(const quint64 commandId, const QVariantMap &parameters)
{
    QMap<quint64, std::function<void(const QVariantMap&)>>::iterator iter = _functionHandler.find(commandId);
    if (iter != _functionHandler.end())
    {
        iter.value()(parameters);
    }
    else{
        qCritical() << "Unkown command id: " << commandId;
    }
}


// *** UI function ***

void EventDispatcher::sendSignUpRequest(const QString &phone, const QString pin)
{
    qint64 phoneNumber = 0;
    qint64 pinCode = 0;

    phoneNumber = phone.toULongLong();
    pinCode = pin.toULongLong();

    QVariantMap parameters;

    parameters[app::signup::phone] = phoneNumber;
    parameters[app::signup::pin] = pinCode;

    emit command(app::signup::id, parameters);
}
void EventDispatcher::sendLogInRequest(const QString &phone, const QString pin){
    qint64 phoneNumber = 0;
    qint64 pinCode = 0;

    phoneNumber = phone.toULongLong();
    pinCode = pin.toULongLong();

    QVariantMap parameters;

    parameters[app::login::phone] = phoneNumber;
    parameters[app::login::pin] = pinCode;

    emit command(app::login::id, parameters);
}

// *** Client function ***

void EventDispatcher::connection(const QVariantMap &parameters)
{
    Q_UNUSED(parameters);

    ParameterHandler ph(parameters);

    bool connected;

    if(!ph.handle(connected, app::connection::connected)) {
        setServerConnected(false);
        return;
    }

    setServerConnected(true);
}


// *** Others ***

bool EventDispatcher::serverConnected() const
{
    return _serverConnected;
}
void EventDispatcher::setServerConnected(bool newServerConnected)
{
    if (_serverConnected == newServerConnected)
        return;
    _serverConnected = newServerConnected;
    emit serverConnectedChanged();
}

int EventDispatcher::userAuthorization() const
{
    return _userAuthorization;
}
void EventDispatcher::setUserAuthorization(int newUserAuthorization)
{
    if (_userAuthorization == newUserAuthorization)
        return;
    _userAuthorization = newUserAuthorization;
    emit userAuthorizationChanged();
}

QString EventDispatcher::serverMessage() const
{
    return _serverMessage;
}
void EventDispatcher::setServerMessage(const QString &newServerMessage)
{
    if (_serverMessage == newServerMessage)
        return;
    _serverMessage = newServerMessage;
    emit serverMessageChanged();
}

QColor EventDispatcher::serverMessageColor() const
{
    return _serverMessageColor;
}
void EventDispatcher::setServerMessageColor(const QColor &newServerMessageColor)
{
    if (_serverMessageColor == newServerMessageColor)
        return;
    _serverMessageColor = newServerMessageColor;
    emit serverMessageColorChanged();
}

int EventDispatcher::userRegistration() const
{
    return _userRegistration;
}
void EventDispatcher::setUserRegistration(int newUserRegistration)
{
    if (_userRegistration == newUserRegistration)
        return;
    _userRegistration = newUserRegistration;
    emit userRegistrationChanged();
}

int EventDispatcher::userRegistrationStep() const
{
    return _userRegistrationStep;
}
void EventDispatcher::setUserRegistrationStep(int newUserRegistrationStep)
{
    if (_userRegistrationStep == newUserRegistrationStep)
        return;
    _userRegistrationStep = newUserRegistrationStep;
    emit userRegistrationStepChanged();
}
