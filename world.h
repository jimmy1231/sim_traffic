#ifndef SIM_TRAFFIC_WORLD_H
#define SIM_TRAFFIC_WORLD_H

#include <cstdio>
#include <tuple>
#include <memory>
#include "prog.h"
#include "rgb.h"
#include "bitmap.h"
#include "dbitmap.h"

/**
 * Prints the raw world - basically a parsed bitmap
 *
 * @param frame_buffer
 * @param width
 * @param height
 */
void
print_world_raw(unsigned char* frame_buffer, unsigned int width, unsigned int height);

class world {
    dbitmap dbmp;
public:
    world(unsigned char *b, size_t h, size_t w) : dbmp{b, h, w} { }
    ~world();

    bitmap &get_bmp();
    dbitmap &get_dbmp();
};

#endif //SIM_TRAFFIC_WORLD_H
