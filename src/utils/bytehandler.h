#ifndef BYTEHANDLER_H
#define BYTEHANDLER_H

#include <QObject>
#include <QDebug>

class ByteHandler : public QObject
{
    Q_OBJECT
public:
    explicit ByteHandler(QObject *parent = nullptr);

    template<typename  T>
    T toInt(const QByteArray& data);

    template<typename T>
    QByteArray toByteProtocol(const QString &name, T &value, qint16 size);

private:
    bool validData(const QByteArray& data, qint64 lenght);
};

#endif // BYTEHANDLER_H
