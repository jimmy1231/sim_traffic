//
// Created by jimmy on 2020-11-30.
//

#ifndef SIM_TRAFFIC_TUNNEL_H
#define SIM_TRAFFIC_TUNNEL_H


#include "world.h"
#include "bb.h"

class tunnel {

public:
    bb *box;
    unsigned char *bitmap;

    tunnel() {

    }
};


#endif //SIM_TRAFFIC_TUNNEL_H
