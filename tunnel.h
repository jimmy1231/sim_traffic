//
// Created by jimmy on 2020-11-30.
//

#ifndef SIM_TRAFFIC_TUNNEL_H
#define SIM_TRAFFIC_TUNNEL_H


#include "prog.h"
#include "bitmap.h"
#include "BB.h"
#include "entity.h"

class tunnel : public entity {
public:
    explicit tunnel(BB &&b) : entity(b) { }
    explicit tunnel(BB &b) : entity(b) { }

    void link(entity *other) override;
    inline std::string name() override;
};


#endif //SIM_TRAFFIC_TUNNEL_H
