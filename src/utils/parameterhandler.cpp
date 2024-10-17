#include "parameterhandler.h"


ParameterHandler::ParameterHandler(const QVariantMap &parameters)
    : _parameters(parameters)
{
}

// // Реализация шаблонных методов
// template<int fieldStatus, typename T>
// bool ParameterHandler::saveTo(T& variable, const QString& key)
// {
//     auto iter = _parameters.find(key);
//     if (iter != _parameters.end() && iter->canConvert<T>())
//     {
//         variable = iter->value<T>();
//         return true;
//     }
//     return isOptional<fieldStatus>("Mandatory field not found or conversion failed, field name: ", key);
// }

// template<int fieldStatus>
// bool ParameterHandler::isOptional(const char* msg, const QString& name)
// {
//     if (fieldStatus == mandatory)
//     {
//         qWarning() << msg << name;
//         return false;
//     }
//     return true;
// }
