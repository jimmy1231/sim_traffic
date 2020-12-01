#include "world.h"
#include <cstdio>

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

bitmap &world::get_bmp() {
    return dbmp;
}

world::~world() {
}

dbitmap &world::get_dbmp() {
    return dbmp;
}
