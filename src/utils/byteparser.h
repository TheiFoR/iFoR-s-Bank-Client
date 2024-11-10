#ifndef BYTEPARSER_H
#define BYTEPARSER_H

#include <QObject>
#include <QDebug>
#include <QVariant>
#include <QIODevice>

#include "../types/package.h"

class ByteParser : public QObject
{
    Q_OBJECT
public:
    explicit ByteParser(QObject *parent = nullptr);

    Package parse(const QByteArray& data);
    QByteArray unparse(const Package& package);

    QByteArray serialize(const QVariantMap& data);
    QVariantMap deserialize(const QByteArray& data, qint64 offset = 0);

    template<typename  T>
    inline T toInt(const QByteArray& data, qint64 offset = 0)
    {
        if(!validData(data, sizeof(T))){
            qWarning() << "Invalid data!";
        }
        QDataStream stream(data);
        stream.setByteOrder(QDataStream::LittleEndian);
        stream.skipRawData(offset);
        T value;
        stream >> value;
        return value;
    }

    template<typename  T>
    inline QByteArray fromInt(const T& number)
    {
        qint8 size = sizeof(T);
        QByteArray result(size, 0x00);
        for(qint8 i = 0; i < size; ++i){
            result[i] = number & (0xFF << 8 * (size - i - 1));
        }
        return result;
    }

private:
    bool validData(const QByteArray& data, qint64 lenght);
};

#endif // BYTEPARSER_H
