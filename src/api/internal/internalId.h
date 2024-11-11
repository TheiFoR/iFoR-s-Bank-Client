#ifndef INTERNALID_H
#define INTERNALID_H

#include "qtypes.h"
#include <unordered_map>
#include <string>

class ApiRegistry {
public:
    static ApiRegistry& instance() {
        static ApiRegistry instance;
        return instance;
    }

    quint8 getId(const std::string& apiName, const std::string& fullNamespace) {
        std::string key = fullNamespace + "::" + apiName;

        auto it = apiIds.find(key);
        if (it != apiIds.end()) {
            return it->second;
        }
        apiIds[key] = currentId++;
        return apiIds[key];
    }

private:
    ApiRegistry() = default;
    ApiRegistry(const ApiRegistry&) = delete;
    ApiRegistry& operator=(const ApiRegistry&) = delete;

    std::unordered_map<std::string, quint64> apiIds;

    quint64 currentId = 0;
};

#endif // INTERNALID_H
