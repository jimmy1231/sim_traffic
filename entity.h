//
// Created by jimmy on 2020-12-03.
//

#ifndef SIM_TRAFFIC_ENTITY_H
#define SIM_TRAFFIC_ENTITY_H

#include <string>

#include "prog.h"
#include "BB.h"
#include "dbitmap.h"

class entity {
public:
    BB box;
    dbitmap dbmp;

    explicit entity(BB &b) : box{b}, dbmp{b.height(), b.width()} { }

    virtual void link(entity *other) = 0;
    virtual std::string name() = 0;
};


#endif //SIM_TRAFFIC_ENTITY_H
