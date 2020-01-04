#include "load.h"
#include <stdio.h>
#include "loadbmp.h"

void
load_world(char *input, FILE* config)
{
	unsigned char *frame_buffer = nullptr;
	unsigned int width, height;

	// TODO: continue from here
	loadbmp_decode_file(input, &frame_buffer, &width, &height, LOADBMP_RGB);
}