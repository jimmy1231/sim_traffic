//
// Created by jimmy on 2020-12-03.
//

#ifndef SIM_TRAFFIC_STATION_H
#define SIM_TRAFFIC_STATION_H

#include <string>

#include "entity.h"
#include "BB.h"

class station : public entity {
public:
    explicit station(BB &&b) : entity(b) { }
    explicit station(BB &b) : entity(b) { }

    void link(entity *other) override;
    inline std::string name() override;
};


#endif //SIM_TRAFFIC_STATION_H
