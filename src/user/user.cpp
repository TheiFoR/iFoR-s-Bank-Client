#include "user.h"

User::User(QObject *parent)
    : QObject{parent}
{}

QString User::name() const
{
    return _name;
}
void User::setName(const QString &newName)
{
    if (_name == newName)
        return;
    _name = newName;
    emit nameChanged();
}

double User::rate() const
{
    return _rate;
}
void User::setRate(double newRate)
{
    if (qFuzzyCompare(_rate, newRate))
        return;
    _rate = newRate;
    emit rateChanged();
}
