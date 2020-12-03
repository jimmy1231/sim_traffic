//
// Created by jimmy on 2020-12-03.
//

#include "tunnel.h"
#include "station.h"
#include "platform.h"
#include "spawn.h"

void station::link(entity *other) {
    {
        auto *ptr = dynamic_cast<station *>(other);
        if (ptr != nullptr) {
            // TODO
        }
    }

    {
        auto *ptr = dynamic_cast<platform *>(other);
        if (ptr != nullptr) {
            // TODO
        }
    }

    {
        auto *ptr = dynamic_cast<tunnel *>(other);
        if (ptr != nullptr) {
            // TODO
        }
    }

    {
        auto *ptr = dynamic_cast<spawn *>(other);
        if (ptr != nullptr) {
            // TODO
        }
    }
}

inline std::string station::name() {
    return "station";
}
