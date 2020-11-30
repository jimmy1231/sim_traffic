#ifndef SIM_TRAFFIC_WORLD_H
#define SIM_TRAFFIC_WORLD_H

#include <cstdio>
#include <tuple>
#include <memory>
#include "rgb.h"
#include "bitmap.h"

/**
 * Prints the raw world - basically a parsed bitmap
 *
 * @param frame_buffer
 * @param width
 * @param height
 */
void
print_world_raw(unsigned char* frame_buffer, unsigned int width, unsigned int height);

typedef std::tuple<size_t, size_t> coords_t;
typedef std::shared_ptr<coords_t> smart_coords_t;

#define POS(row, col, w, h) ((row)*(w) + (col))*3
#define SET_VISITED(frame, i) frame[i] = 112; \
	frame[i+1] = 16; \
	frame[i+2] = 81
#define MATCH(frame,i,r,g,b) frame[i] == (r) && frame[i+1] == (g) && frame[i+2] == (b)

#define MAX(s1, s2) (s1) > (s2) ? (s1) : (s2)
#define MIN(s1, s2) (s1) < (s2) ? (s1) : (s2)

class world {
    bitmap *bmp;
public:
    explicit world(bitmap *_bmp) : bmp{_bmp} { }
    world(const world &w) : bmp{w.bmp->make_cpy()} { };
    world(unsigned char *b, size_t h, size_t w)
        : bmp{new bitmap(b, h, w)} { }
    ~world();

    world *make_cpy() const;
    bitmap& get_bmp();
};

#endif //SIM_TRAFFIC_WORLD_H
