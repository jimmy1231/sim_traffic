#include "world.h"
#include "prog.h"
#include "rgb.h"
#include <cstdio>

rgb CLR_TUNNEL = rgb(0, 128, 0);
rgb CLR_WHITE = rgb(255, 255, 255);
rgb CLR_BLACK = rgb(0, 0, 0);
rgb CLR_DISCOVERY_VISITED = rgb(164, 93, 193);

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
