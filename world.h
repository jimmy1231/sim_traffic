#ifndef SIM_TRAFFIC_WORLD_H
#define SIM_TRAFFIC_WORLD_H

#include <cstdio>
#include <tuple>
#include <vector>
#include <memory>

#include "prog.h"
#include "rgb.h"
#include "bitmap.h"
#include "dbitmap.h"
#include "entity.h"
#include "station.h"
#include "platform.h"
#include "spawn.h"
#include "tunnel.h"

/**
 * Prints the raw world - basically a parsed bitmap
 *
 * @param frame_buffer
 * @param width
 * @param height
 */
void print_world_raw(unsigned char* frame_buffer, unsigned int width, unsigned int height);
void print_bmp(unsigned char* frame_buffer, unsigned int width, unsigned int height);

class world {
    dbitmap dbmp;
public:
    std::vector<tunnel *> tunnels;
    std::vector<station *> stations;
    std::vector<platform *> platforms;
    std::vector<spawn *> spawns;

    world(unsigned char *b, size_t h, size_t w) : dbmp{b, h, w} { }
    ~world();

    void calibrate();
    void copy_from(entity &entity);
    bitmap &get_bmp();
    dbitmap &get_dbmp();
    void link(entity *ent);
};

#endif //SIM_TRAFFIC_WORLD_H
