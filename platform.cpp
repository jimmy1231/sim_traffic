//
// Created by jimmy on 2020-12-03.
//

#include <sstream>
#include <string>

#include "tunnel.h"
#include "station.h"
#include "platform.h"
#include "spawn.h"

void platform::link(entity *other) {
    {
        auto *ptr = dynamic_cast<station *>(other);
        if (ptr != nullptr) {
            if (!station_) {
                station_ = ptr;
            } else {
                std::cout << "WARNING: Platform cannot be linked with more than 1 station" << std::endl;
            }
            return;
        }
    }

    {
        auto *ptr = dynamic_cast<platform *>(other);
        if (ptr != nullptr) {
            warn_illegal_link(this, other);
            return;
        }
    }

    {
        auto *ptr = dynamic_cast<tunnel *>(other);
        if (ptr != nullptr) {
            if (!tunnel_) {
                tunnel_ = ptr;
            } else {
                std::cout << "WARNING: Platform cannot be linked with more than 1 tunnel" << std::endl;
            }
            return;
        }
    }

    {
        auto *ptr = dynamic_cast<spawn *>(other);
        if (ptr != nullptr) {
            warn_illegal_link(this, other);
            return;
        }
    }
}

inline std::string platform::name() {
    std::stringstream sstream;
    sstream << "platform" << box.top_left().str();
    return sstream.str();
}
