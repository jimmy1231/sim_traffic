//
// Created by jimmy on 2020-12-03.
//

#ifndef SIM_TRAFFIC_PLATFORM_H
#define SIM_TRAFFIC_PLATFORM_H

#include <string>

#include "entity.h"
#include "BB.h"

class platform : public entity {
public:
    explicit platform(BB &b) : entity(b) { }
    explicit platform(BB &&b) : entity(b) { }

    void link(entity *other) override;
    inline std::string name() override;
};


#endif //SIM_TRAFFIC_PLATFORM_H
