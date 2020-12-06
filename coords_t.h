//
// Created by jimmy on 2020-12-02.
//

#ifndef SIM_TRAFFIC_COORDS_T_H
#define SIM_TRAFFIC_COORDS_T_H

#include <string>
#include <sstream>

class coords_t {
public:
    size_t row;
    size_t col;

    coords_t() = default;
    coords_t(size_t r, size_t c) : row(r), col(c) { }
    coords_t(const coords_t &other) = default;
    coords_t(coords_t &&other) = default;

    inline std::string str() const {
        std::stringstream sstream;
        sstream << "(" << row << "," << col << ")";
        return sstream.str();
    }
    coords_t &operator=(const coords_t &other) = default;
    coords_t &operator=(coords_t &&other) = default;
    bool operator<(const coords_t &other) const;
    bool operator<(coords_t &&other) const;
    bool operator<=(const coords_t &other) const;
    bool operator<=(coords_t &&other) const;
    bool operator>(const coords_t &other) const;
    bool operator>(coords_t &&other) const;
    bool operator>=(const coords_t &other) const;
    bool operator>=(coords_t &&other) const;
};

#endif //SIM_TRAFFIC_COORDS_T_H
