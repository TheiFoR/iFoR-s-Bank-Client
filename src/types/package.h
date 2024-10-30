#ifndef PACKAGE_H
#define PACKAGE_H

#include <QVariantMap>
#include <cstdint>

struct Package{
    uint16_t id;
    QVariantMap data;
};

#endif // PACKAGE_H
