#include <cstdio>

#include "world.h"
#include "prog.h"
#include "rgb.h"
#include "station.h"
#include "platform.h"
#include "spawn.h"
#include "tunnel.h"

rgb CLR_TUNNEL = rgb(0, 128, 0);
rgb CLR_STATION = rgb(0, 0, 0);
rgb CLR_SPAWN_POINT = rgb(224, 32, 64);
rgb CLR_PLATFORM = rgb(255, 255, 0);
rgb CLR_WHITE = rgb(255, 255, 255);
rgb CLR_BLACK = rgb(0, 0, 0);
rgb CLR_DVISITED = rgb(164, 93, 193);
rgb CLR_DCURRENT = rgb(247, 199, 72);

void
print_world_raw(unsigned char* frame_buffer,
                unsigned int width,
                unsigned int height)
{
	printf("WORLD: %dx%d\n", width, height);
	int row, col, frame_pos=0;
	for (row=0; row<height; row++) {
		for (col=0; col<width; col++, frame_pos+=3) {
			printf("(%3d,%3d,%3d)",
				frame_buffer[frame_pos],
				frame_buffer[frame_pos+1],
				frame_buffer[frame_pos+2]
				);
			
			if (col != width-1) {
				printf(",");
			}
		}
		printf("\n");
	}
}

void
print_bmp(unsigned char* frame_buffer,
          unsigned int width,
          unsigned int height)
{
    printf("BMP: %dx%d\n", width, height);
    int row, col, frame_pos=0;
    for (row=0; row<height; row++) {
        for (col=0; col<width; col++, frame_pos+=3) {
            if (frame_buffer[frame_pos] != CLR_WHITE.r ||
                frame_buffer[frame_pos+1] != CLR_WHITE.r ||
                frame_buffer[frame_pos+2] != CLR_WHITE.r) {
                printf(" ");
            } else {
                printf("0");
            }
        }

        printf("\n");
    }
}

bitmap &world::get_bmp() {
    return dbmp;
}

world::~world() {
}

dbitmap &world::get_dbmp() {
    return dbmp;
}

void world::link(entity *ent) {
    {
        auto *ptr = dynamic_cast<station *>(ent);
        if (ptr != nullptr) {
            stations.push_back(ptr);
        }
    }

    {
        auto *ptr = dynamic_cast<platform *>(ent);
        if (ptr != nullptr) {
            platforms.push_back(ptr);
        }
    }

    {
        auto *ptr = dynamic_cast<tunnel *>(ent);
        if (ptr != nullptr) {
            tunnels.push_back(ptr);
        }
    }

    {
        auto *ptr = dynamic_cast<spawn *>(ent);
        if (ptr != nullptr) {
            spawns.push_back(ptr);
        }
    }
}
