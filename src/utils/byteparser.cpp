#include "byteparser.h"

ByteParser::ByteParser(QObject *parent)
    : QObject{parent}
{}

Package ByteParser::parse(const QByteArray &data)
{
    Package package;
    package.id = toInt<quint16>(QByteArray(data.data(), 2));
    package.data = deserialize(data, 2);
    return package;
}
QByteArray ByteParser::unparse(const Package &package)
{
    QByteArray data;
    data.append(fromInt(package.id));
    data.append(serialize(package.data));
    return data;
}

QByteArray ByteParser::serialize(const QVariantMap &data)
{
    QByteArray result;

    QDataStream outStream(&result, QIODevice::WriteOnly);
    outStream << data;
    return result;
}
QVariantMap ByteParser::deserialize(const QByteArray &data, qint64 offset)
{
    QByteArray fitData{const_cast<QByteArray*>(&data)->data() + offset, data.size() - offset};
    QVariantMap result;
    QDataStream inStream(&fitData, QIODevice::ReadOnly);
    inStream >> result;
    return result;
}

bool ByteParser::validData(const QByteArray& data, qint64 lenght)
{
    if(data.size() != lenght){
        return false;
    }
    return true;
}
