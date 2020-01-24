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
 *
 * @param output_file
 * @param frame_buffer
 * @param width If frame_buffer were a NxM matrix, width would be M
 * @param tl top right coordinates
 * @param br bottom right coordinates
 * @param channels number of channels (e.g. rgba=4, rgb=3)
 */
void
write_ppm(std::string &output_file, unsigned char *frame_buffer,
	size_t width,
	coords_t &tl, coords_t &br,
	size_t channels)
{
	assert(channels == 1 || channels == 3);

	std::ofstream ofs;
	ofs.open(output_file);

	size_t ROW_LOWER = get<0>(tl);
	size_t COL_LOWER = get<1>(tl);
	size_t ROW_UPPER = get<0>(br);
	size_t COL_UPPER = get<1>(br);

	ofs << (channels > 1 ? "P3" : "P2") << std::endl;
	ofs << (COL_UPPER-COL_LOWER+1) << " ";
	ofs << (ROW_UPPER-ROW_LOWER+1) << std::endl;
	ofs << 255 << std::endl;

	size_t i, n;
	size_t row, col;
	for (row=ROW_LOWER; row<=ROW_UPPER; row++) {
		for (col=COL_LOWER; col<=COL_UPPER; col++) {
			i = (col + row*width) * channels;

			for (n=0; n<channels; n++) {
				ofs << (int)(frame_buffer[i+n]) << " ";
			}
		}
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

	if (!found) {
#ifdef DEBUG
		printf("No tunnels found. Cannot discover\n");
#endif
		return;
	}

	/*
	 * Breadth-first discovery of first tunnel. Afterwards,
	 * use this tunnel as the epicenter for breadth-first
	 * exhaustive discovery of the entire world.
	 *
	 * Find the diagonal corners:
	 * Upper-left	: row_ul, col_ul
	 * Bottom-right	: row_br, col_br
	 */
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

	size_t row_ul, col_ul, row_br, col_br;
	row_ul = row_br = row;
	col_ul = col_br = col;
	while (!Q.empty()) {
		_c = Q.front();
		Q.pop();

		_row = std::get<0>(*_c);
		_col = std::get<1>(*_c);

		/* Diagonal corners */
		row_ul = MIN(_row, row_ul);
		col_ul = MIN(_col, col_ul);
		row_br = MAX(_row, row_br);
		col_br = MAX(_col, col_br);

		if (_row-1 >= 0) { // Up
			_c = set_visited(_row-1, _col);
			if (_c != nullptr)
				Q.push(_c);
		}
		if (_row+1 < height) { // Down
			_c = set_visited(_row+1, _col);
			if (_c != nullptr)
				Q.push(_c);
		}
		if (_col-1 >= 0) { // Left
			_c = set_visited(_row, _col-1);
			if (_c != nullptr)
				Q.push(_c);
		}
		if (_col+1 < width) { // Right
			_c = set_visited(_row, _col+1);
			if (_c != nullptr)
				Q.push(_c);
		}
	}

	coords_t ul = make_tuple(row_ul, col_ul);
	coords_t br = make_tuple(row_br, col_br);
#ifdef DEBUG
	printf("UpLeft: (%d, %d); BottomRight: (%d, %d)\n",
		   (int)row_ul, (int)col_ul,
		   (int)row_br, (int)col_br);
	string filename = "tunnel.ppm";
	write_ppm(filename, world,
		(size_t)width, ul, br, (size_t)3);
#endif
}

void
load_world(char *input, FILE* config)
{
	unsigned char *frame_buffer = nullptr;
	unsigned int width, height;

	/* Load BMP file as bytes - each byte = 1 channel */
	loadbmp_decode_file(input, &frame_buffer,
		&width, &height, LOADBMP_RGB);
#ifdef DEBUG
	printf("Finished load into frame_buffer: %dx%d\n", width, height);
	print_world_raw(frame_buffer, width, height);
#endif

	vector<struct piece> V;
	vector<struct edge> E;
	discover(frame_buffer, (size_t)height, (size_t)width, V, E);

#ifdef DEBUG
	string filename = "discovered.ppm";
	coords_t tl = make_tuple(0, 0);
	coords_t br = make_tuple(height-1, width-1);
	write_ppm(filename, frame_buffer,
		(size_t)width, tl, br, (size_t)3);
#endif
}