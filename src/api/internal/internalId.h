#ifndef INTERNALID_H
#define INTERNALID_H

#include "qtypes.h"
#include <unordered_map>
#include <string>

class ApiRegistry {
public:
    // Метод для получения инстанса одиночки
    static ApiRegistry& instance() {
        static ApiRegistry instance;
        return instance;
    }

    // Метод для получения ID с учётом полного пути (пространства имён)
    quint8 getId(const std::string& apiName, const std::string& fullNamespace) {
        // Формируем ключ для хранилища: полное пространство имён + имя API
        std::string key = fullNamespace + "::" + apiName;

        auto it = apiIds.find(key);
        if (it != apiIds.end()) {
            // Если ID уже существует, возвращаем его
            return it->second;
        }
        // Если ID не существует, создаём новый
        apiIds[key] = currentId++;
        return apiIds[key];
    }

private:
    // Закрытый конструктор, чтобы предотвратить создание объекта извне
    ApiRegistry() = default;
    ApiRegistry(const ApiRegistry&) = delete;  // Запрещаем копирование
    ApiRegistry& operator=(const ApiRegistry&) = delete;  // Запрещаем присваивание

    // Хранилище для уже сгенерированных ID, с учётом полных пространств имён
    std::unordered_map<std::string, quint64> apiIds;

    // Текущий счётчик ID
    quint64 currentId = 0;
};

#endif // INTERNALID_H
