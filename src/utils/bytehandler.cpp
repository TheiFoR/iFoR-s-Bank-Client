#include "bytehandler.h"

ByteHandler::ByteHandler(QObject *parent)
    : QObject{parent}
{}

bool ByteHandler::validData(const QByteArray& data, qint64 lenght)
{
    if(data.size() != lenght){
        return false;
    }
    return true;
}

template<typename T>
T ByteHandler::toInt(const QByteArray &data)
{
    if(!validData(data, sizeof(T))){
        qWarning() << "Invalid data!";
    }
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);
    T value;
    stream >> value;
    return value;
}

template<typename T>
QByteArray ByteHandler::toByteProtocol(const QString& name, T &value, qint16 size)
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
