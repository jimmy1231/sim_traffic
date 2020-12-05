//
// Created by jimmy on 2020-12-03.
//

#ifndef SIM_TRAFFIC_SPAWN_H
#define SIM_TRAFFIC_SPAWN_H

#include <string>

#include "entity.h"
#include "BB.h"

class spawn : public entity {
public:
    explicit spawn(BB &&b) : entity(b, CLR_SPAWN_POINT) { }
    explicit spawn(BB &b) : entity(b, CLR_SPAWN_POINT) { }

    void link(entity *other) override;
    inline std::string name() override;
};


#endif //SIM_TRAFFIC_SPAWN_H
