#ifndef SETTINGS_H
#define SETTINGS_H

#include <QHostAddress>

class Settings
{
public:
    inline static const QHostAddress ip = QHostAddress("127.0.0.1");
    inline static const quint16 port = 1310;
};

#endif // SETTINGS_H
