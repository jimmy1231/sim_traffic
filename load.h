#ifndef SIM_TRAFFIC_LOAD_H
#define SIM_TRAFFIC_LOAD_H

#include <cstdio>

#define LOADBMP_RGB 3
/**
 * Initializes the world using the bitmap taken from 'input',
 * sets pre-determined values specified in 'config'.
 *
 * Returns a data structure which represents the world.
 */
void
load_world(char *input, FILE* config);

#endif //SIM_TRAFFIC_LOAD_H
