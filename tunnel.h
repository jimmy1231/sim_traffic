//
// Created by jimmy on 2020-11-30.
//

#ifndef SIM_TRAFFIC_TUNNEL_H
#define SIM_TRAFFIC_TUNNEL_H


#include "prog.h"
#include "bitmap.h"
#include "bb.h"

class tunnel {

public:
    bb box;
    dbitmap dbmp;

    explicit tunnel(bb &&b) :
        box{b},
        dbmp{b.height(), b.width()} { }
};


#endif //SIM_TRAFFIC_TUNNEL_H
