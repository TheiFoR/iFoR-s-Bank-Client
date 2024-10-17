#ifndef SERVERAUTHORIZATION_H
#define SERVERAUTHORIZATION_H

#include "../def.h"

namespace server{
    namespace request{
        API(login, 0){
            API_FIELD(phone)    // M, int64_t
            API_FIELD(pin)      // M, int32_t
        }
        API(signup, 1){
            API_FIELD(phone)    // M, int64_t
            API_FIELD(pin)      // M, int32_t
        }
    }
    namespace response{
        API(login, 0){
            API_FIELD(code)     // M, int64_t
            API_FIELD(message)  // O, string
        }
        API(signup, 1){
            API_FIELD(code)     // M, int64_t
            API_FIELD(message)  // O, string
        }
    }
}

#endif // SERVERAUTHORIZATION_H
