//
// Created by jimmy on 2020-11-30.
//

#include <sstream>
#include <string>

#include "tunnel.h"
#include "station.h"
#include "platform.h"
#include "spawn.h"

void tunnel::link(entity *other) {
    {
        auto *ptr = dynamic_cast<station *>(other);
        if (ptr != nullptr) {
            warn_illegal_link(this, ptr);
            return;
        }
    }

    {
        auto *ptr = dynamic_cast<platform *>(other);
        if (ptr != nullptr) {
            if (!platform1) {
                platform1 = ptr;
            } else if (!platform2) {
                platform2 = ptr;
            } else {
                std::cout << "WARNING: Tunnel linked to more than 2 platforms" << std::endl;
            }
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

inline std::string tunnel::name() {
    std::stringstream sstream;
    sstream << "tunnel" << box.top_left().str();
    return sstream.str();
}
