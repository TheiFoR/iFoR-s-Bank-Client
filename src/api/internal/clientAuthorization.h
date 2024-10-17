#ifndef CLIENTAUTHORIZATION_H
#define CLIENTAUTHORIZATION_H

#include "../def.h"

namespace app{

    API_G(signup) {
        API_FIELD(phone)
        API_FIELD(pin)
    }

    API_G(login) {
        API_FIELD(phone)
        API_FIELD(pin)
    }

}

#endif // CLIENTAUTHORIZATION_H
