#ifndef CLIENTAUTHORIZATION_H
#define CLIENTAUTHORIZATION_H

#include "../def.h"

namespace app{
namespace request{
namespace authorization{

API_G(signup) {
    API_FIELD(phone) // M, int64_t
    API_FIELD(pin)   // M, int64_t
}

API_G(login) {
    API_FIELD(phone) // M, int64_t
    API_FIELD(pin)   // M, int64_t
}

} // authorization
} // request

namespace response{
namespace authorization{

API_G(login) {
    API_FIELD(code)     // M, int, see enums.h login::code
    API_FIELD(message)  // O, string
}

} // authorization
} // response
} // app

#endif // CLIENTAUTHORIZATION_H
