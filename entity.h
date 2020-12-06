//
// Created by jimmy on 2020-12-03.
//

#ifndef SIM_TRAFFIC_ENTITY_H
#define SIM_TRAFFIC_ENTITY_H

#include <iostream>
#include <string>

#include "prog.h"
#include "BB.h"
#include "dbitmap.h"

class entity {
public:
    BB box;
    rgb color_code;
    dbitmap dbmp;

    explicit entity(BB &b, rgb &c) : box{b}, dbmp{b.height(), b.width()}, color_code(c) { }

    virtual void link(entity *other) = 0;
    virtual std::string name() = 0;
};

inline void warn_illegal_link(entity *ent, entity *other) {
    std::cout << "WARNING: Illegal link, " << ent->name() << " -> " << other->name() << std::endl;
}


#endif //SIM_TRAFFIC_ENTITY_H
