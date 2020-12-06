//
// Created by jimmy on 2020-12-03.
//

#ifndef SIM_TRAFFIC_STATION_H
#define SIM_TRAFFIC_STATION_H

#include <string>
#include <vector>

#include "entity.h"
#include "BB.h"

class station : public entity {
    std::vector<platform *> platforms;
    std::vector<spawn *> spawns;
public:
    explicit station(BB &&b) : entity(b, CLR_STATION) { }
    explicit station(BB &b) : entity(b, CLR_STATION) { }

    void link(entity *other) override;
    inline std::string name() override;
};


#endif //SIM_TRAFFIC_STATION_H
