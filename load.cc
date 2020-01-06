#include "load.h"
#include <stdio.h>
#include "loadbmp.h"
#include "sim.h"
#include "world.h"

void
load_world(char *input, FILE* config)
{
	unsigned char *frame_buffer = nullptr;
	unsigned int width, height;

	loadbmp_decode_file(input, &frame_buffer, &width, &height, LOADBMP_RGB);
#ifdef DEBUG
	printf("Finished load into frame_buffer: %dx%d\n", width, height);
	print_world_raw(frame_buffer, width, height);
#endif
}