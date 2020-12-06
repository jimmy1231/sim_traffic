//
// Created by jimmy on 2020-11-30.
//

#ifndef SIM_TRAFFIC_RGB_H
#define SIM_TRAFFIC_RGB_H

#include <string>

class rgb {
public:
    unsigned char r, g, b;
    rgb() = default;
    rgb(const rgb &other) = default;
    rgb(rgb &&other) = default;
    rgb(unsigned char r, unsigned char g, unsigned char b)
        : r{r}, g{g}, b{b}
        { }

    std::string str() const;
    unsigned char average() const;
    bool operator==(const rgb &other) const;
    bool operator!=(const rgb &other) const;
    rgb &operator=(const rgb &other);
};


#endif //SIM_TRAFFIC_RGB_H
