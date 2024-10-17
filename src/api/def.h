#ifndef DEF_H
#define DEF_H

#include "qtypes.h"
#include "internal/internalId.h"

#define API_G(name) \
namespace name{\
    const quint64 id = ApiRegistry::instance().getId(#name, __FUNCTION__);\
}\
namespace name

#define API(name, api_id) \
namespace name{\
    const quint64 id = api_id;\
}\
namespace name

#define API_FIELD(name) \
    constexpr char name[] = #name;

#endif // DEF_H
