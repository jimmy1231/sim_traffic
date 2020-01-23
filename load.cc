#include "load.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>
#include <memory>
#include <queue>
#include "loadbmp.h"
#include "sim.h"
#include "world.h"

using namespace std;
/**
 * Writes frame_buffer to a file specified by output_file as a
 * PPM file. If number of channels is 3, then use P3 format, else
 * (if single channel - e.g. grayscale) use P2.
 *
 * See Wikipedia table:
 * https://en.wikipedia.org/wiki/Netpbm_format
 */
void
write_ppm(std::string &output_file, unsigned char *frame_buffer,
	size_t width, size_t height, size_t channels)
{
	assert(channels == 1 || channels == 3);

	std::ofstream ofs;
	ofs.open(output_file);

	ofs << (channels > 1 ? "P3" : "P2") << std::endl;
	ofs << width << " " << height << std::endl;
	ofs << 255 << std::endl;

	std::size_t i;
	for (i=0; i<width*height*channels; i++) {
		ofs << (int)(frame_buffer[i]) << " ";
	}
	ofs.close();
}

void
discover(unsigned char *world, size_t height, size_t width,
	std::vector<struct piece> &V,
	std::vector<struct edge> &E)
{
	size_t frame_pos = 0, row, col;
	bool found = false;
	for (row=0; row<height; row++) {
		for (col=0; col<width; col++, frame_pos+=3) {
			/* Discover the first tile */
			if (world[frame_pos] == 0 &&
				world[frame_pos+1] == 128 &&
				world[frame_pos+2] == 0) {
				printf("Found!\n");
				found = true;
				break;
			}
		}
		if (found) {
			break;
		}
	}

	/* Breadth-first discovery of first edge */

	queue<smart_coords_t> Q;
	SET_VISITED(world, frame_pos);
	Q.push(make_shared<coords_t>(make_tuple(row, col)));

	auto set_visited = [&width, &height, &world]
		(size_t row, size_t col) -> smart_coords_t
	{
	  size_t _pos = POS(row, col, width, height);
	  if (MATCH(world, _pos, 0, 128, 0)) {
		  SET_VISITED(world, _pos);
		  return make_shared<coords_t>(make_tuple(row, col));
	  }
	  return nullptr;
	};

	smart_coords_t _c;
	size_t _row, _col;
	while (!Q.empty()) {
		_c = Q.front();
		Q.pop();

		_row = std::get<0>(*_c);
		_col = std::get<1>(*_c);

		if (_row-1 >= 0) { // Up
			if ((_c = set_visited(_row-1, _col)) != nullptr)
				Q.push(_c);
		}
		if (_row+1 < height) { // Down
			if ((_c = set_visited(_row+1, _col)) != nullptr)
				Q.push(_c);
		}
		if (_col-1 >= 0) { // Left
			if ((_c = set_visited(_row, _col-1)) != nullptr)
				Q.push(_c);
		}
		if (_col+1 < width) { // Right
			if ((_c = set_visited(_row, _col+1)) != nullptr)
				Q.push(_c);
		}
	}
}

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

	vector<struct piece> V;
	vector<struct edge> E;
	discover(frame_buffer, (size_t)height, (size_t)width, V, E);

#ifdef DEBUG
	string filename = "discovered.ppm";
	write_ppm(filename, frame_buffer,
		(size_t)width, (size_t)height, (size_t)3);
#endif
}