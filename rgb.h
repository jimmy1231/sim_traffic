//
// Created by jimmy on 2020-11-30.
//

#ifndef SIM_TRAFFIC_RGB_H
#define SIM_TRAFFIC_RGB_H


class rgb {
public:
    unsigned char r, g, b;
    rgb() = default;
    rgb(unsigned char r, unsigned char g, unsigned char b)
        : r{r}, g{g}, b{b}
        { }

    unsigned char average() const;
    bool operator==(const rgb &other) const;
    rgb &operator=(const rgb &other);
};


#endif //SIM_TRAFFIC_RGB_H
