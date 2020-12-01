//
// Created by jimmy on 2020-11-30.
//

#ifndef SIM_TRAFFIC_DBITMAP_H
#define SIM_TRAFFIC_DBITMAP_H

#include "prog.h"
#include "bitmap.h"
#include <unordered_map>
#include <vector>

typedef std::unordered_map<std::string, rgb> gridmap;
class dbitmap : public bitmap {
    std::vector<gridmap *> dbit_cache;

    void track_pixel(int id, rgb &color, const coords_t &coords);

public:
    dbitmap(unsigned char *b, size_t h, size_t w) : bitmap(b, h, w) { }
    dbitmap(bitmap &&other) : bitmap(other) { };
    dbitmap(const dbitmap &other) : bitmap(other) { };
    dbitmap(dbitmap &&other) :
        bitmap(other.buffer, other.height, other.width),
        dbit_cache{std::move(other.dbit_cache)} { };
    explicit dbitmap(bitmap &bmp) : bitmap(bmp.buffer, bmp.height, bmp.width) { }
    ~dbitmap();

    bool set_visited(int id, rgb &color, const coords_t &coords);
    int mark();
    void reset(int id);
};


#endif //SIM_TRAFFIC_DBITMAP_H
