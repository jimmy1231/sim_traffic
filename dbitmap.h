//
// Created by jimmy on 2020-11-30.
//

#ifndef SIM_TRAFFIC_DBITMAP_H
#define SIM_TRAFFIC_DBITMAP_H

#include "prog.h"
#include "bitmap.h"
#include "coords_t.h"
#include <unordered_map>
#include <vector>

typedef std::unordered_map<std::string, rgb> gridmap;
class dbitmap : public bitmap {
    std::vector<gridmap> dbit_cache;

public:
    dbitmap(size_t h, size_t w) : bitmap(h, w) { }
    dbitmap(unsigned char *b, size_t h, size_t w) : bitmap(b, h, w) { }
    explicit dbitmap(bitmap &&other) : bitmap(other) { };
    dbitmap(const dbitmap &other) : bitmap(other) { };
    dbitmap(dbitmap &&other)  noexcept :
        bitmap(other.buffer, other.height, other.width),
        dbit_cache{std::move(other.dbit_cache)} { };
    explicit dbitmap(bitmap &bmp) : bitmap(bmp.buffer, bmp.height, bmp.width) { }
    ~dbitmap();

    void save(int id, rgb &color, const coords_t &coords);
    int mark();
    void reset(int id);
};


#endif //SIM_TRAFFIC_DBITMAP_H
