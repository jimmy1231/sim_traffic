//
// Created by jimmy on 2020-12-03.
//

#include <sstream>
#include <string>

#include "tunnel.h"
#include "station.h"
#include "platform.h"
#include "spawn.h"

void spawn::link(entity *other) {
    {
        auto *ptr = dynamic_cast<station *>(other);
        if (ptr != nullptr) {
            if (!station_) {
                station_ = ptr;
            } else {
                std::cout << "WARNING: Spawn cannot be linked to more than 1 station" << std::endl;
            }
            return;
        }
    }

    {
        auto *ptr = dynamic_cast<platform *>(other);
        if (ptr != nullptr) {
            warn_illegal_link(this, ptr);
            return;
        }
    }

    {
        auto *ptr = dynamic_cast<tunnel *>(other);
        if (ptr != nullptr) {
            warn_illegal_link(this, ptr);
            return;
        }
    }

    {
        auto *ptr = dynamic_cast<spawn *>(other);
        if (ptr != nullptr) {
            warn_illegal_link(this, ptr);
            return;
        }
    }
}

inline std::string spawn::name() {
    std::stringstream sstream;
    sstream << "spawn" << box.top_left().str();
    return sstream.str();
}
