#include "world.h"
#include <stdio.h>

void
print_world_raw(unsigned char* frame_buffer, unsigned int width, unsigned int height)
{
	printf("======================================================\n");
	printf("WORLD: %dx%d\n", width, height);
	printf("======================================================\n");
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
	printf("======================================================\n");
}