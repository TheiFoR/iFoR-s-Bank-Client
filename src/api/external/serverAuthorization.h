#ifndef SERVERAUTHORIZATION_H
#define SERVERAUTHORIZATION_H

#include "../def.h"

namespace server{
namespace request{
namespace authorization{

API(login, 0){
    API_FIELD(phone)    // M, int64_t
    API_FIELD(pin)      // M, int32_t
}
API(signup, 1){
    API_FIELD(phone)    // M, int64_t
    API_FIELD(pin)      // M, int32_t
}

} // authorization
} // request

namespace response{
namespace authorization{

API(login, 0){
    API_FIELD(code)     // M, int64_t, see enums.h login::code
    API_FIELD(message)  // O, string
    API_FIELD(uid)      // O, uint64_t
}
API(signup, 1){
    API_FIELD(code)     // M, int64_t, see enums.h login::code
    API_FIELD(message)  // O, string
}

} // authorization
} // response
} // server

#endif // SERVERAUTHORIZATION_H
