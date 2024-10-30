#include "byteparser.h"

ByteParser::ByteParser(QObject *parent)
    : QObject{parent}
{}

Package ByteParser::parse(const QByteArray &data)
{
    Package package;
    package.id = toInt<quint16>(QByteArray(data.data(), 2));
    package.data = toQVariantMap(data, 2);
    return package;
}

QByteArray ByteParser::unparse(const Package &package)
{
    QByteArray data;
    data.append(fromInt(package.id));
    data.append(fromQVariantMap(package.data));
    return data;
}

QByteArray ByteParser::fromQVariantMap(const QVariantMap &data)
{
    QByteArray result;

    for(QVariantMap::ConstIterator iter = data.constBegin(); iter != data.constEnd(); ++iter){
        QString name = iter.key();
        QVariant item = iter.value();

        int typeId = item.typeId();

        if (item.canConvert(typeId)) {
            QByteArray bytes;
            if (typeId == QMetaType::Short) {
                short value = *static_cast<short*>(item.data());
                bytes = toByteProtocol(name, value);
            } else if (typeId == QMetaType::LongLong) {
                qint64 value = *static_cast<qint64*>(item.data());
                bytes = toByteProtocol(name, value);
            } else if (typeId == QMetaType::Int) {
                qint32 value = *static_cast<qint32*>(item.data());
                bytes = toByteProtocol(name, value);
            }
            else{
                qCritical() << "Unknown type!";
            }

            result.append(bytes);
        } else {
            qCritical() << "Failed to convert variable.";
        }
    }

    return result;
}

QVariantMap ByteParser::toQVariantMap(const QByteArray &data, qint64 offset)
{
    QVariantMap result;

    qint64 dataSize = data.size();

    qint64 i = 0;
    while(i < dataSize - offset){
        qint16 nameSize = toInt<qint16>(data, offset + i);
        i += 2;
        qint16 valueSize = toInt<qint16>(data, offset + i);
        i += 2;
        QString name = QString(QByteArray(data.data() + offset + i, nameSize));
        i += nameSize;
        QByteArray rawValue(data.data() + offset + i, valueSize);
        i += valueSize;
        result[name] = rawValue;
    }

    return result;
}

QString ByteParser::toString(const QByteArray &data, qint64 offset)
{
    QString result(QByteArray(data.data(), offset));
    return result;
}

bool ByteParser::validData(const QByteArray& data, qint64 lenght)
{
    if(data.size() != lenght){
        return false;
    }
    return true;
}
