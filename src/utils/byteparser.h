#ifndef BYTEPARSER_H
#define BYTEPARSER_H

#include <QObject>
#include <QDebug>
#include <QVariant>

#include "../types/package.h"

class ByteParser : public QObject
{
    Q_OBJECT
public:
    explicit ByteParser(QObject *parent = nullptr);

    Package parse(const QByteArray& data);
    QByteArray unparse(const Package& package);

    QByteArray fromQVariantMap(const QVariantMap& data);
    QVariantMap toQVariantMap(const QByteArray& data, qint64 offset = 0);

    QString toString(const QByteArray &data, qint64 offset);

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

    template<typename T>
    inline QByteArray toByteProtocol(const QString &name, T &value, qint16 size = -1)
    {
        if (size == -1) size = sizeof(T);
        else size *= sizeof(T);

        QByteArray result;

        result.append(static_cast<uchar>(name.size() & 0xFF));
        result.append(static_cast<uchar>((name.size() >> 8) & 0xFF));

        result.append(static_cast<uchar>(size & 0xFF));
        result.append(static_cast<uchar>((size >> 8) & 0xFF));

        result.append(QByteArray(name.toStdString().c_str(), name.size()));

        result.append(reinterpret_cast<const char*>(&value), size);

        result.resize(name.size() + size + 4);

        return result;
    }

private:
    bool validData(const QByteArray& data, qint64 lenght);
};

#endif // BYTEPARSER_H
