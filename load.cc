#include <cstdio>
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <memory>
#include <queue>

#include "load.h"
#include "prog.h"
#include "loadbmp.h"
#include "sim.h"
#include "world.h"
#include "bb.h"
#include "tunnel.h"
#include "rgb.h"
#include "bitmap.h"
#include "dbitmap.h"

using namespace std;

/**
 * Writes frame_buffer to a file specified by output_file as
 * a PPM file. If number of channels is 3, then use P3 format
 * else (if single channel - e.g. grayscale) use P2.
 *
 * See Wikipedia table:
 * https://en.wikipedia.org/wiki/Netpbm_format
 *
 * @param output_file
 * @param frame_buffer
 * @param width If frame_buffer were a NxM matrix, width would
 * be M
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
    std::cout << "writing to: " << output_file
        << ", tl=(" << get_row(tl) << "," << get_col(tl) << "), "
        << "br=("<< get_row(br) << "," << get_col(br) << "), "
        << std::endl;
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
recursive_discover()
{
    /*
     *
     */

}

bb get_bb(world &wrld, coords_t coords)
{
    queue<coords_t> Q;
    Q.push(coords);

    size_t row_ul, col_ul, row_br, col_br;
    row_ul = row_br = get_row(coords);
    col_ul = col_br = get_col(coords);

    dbitmap &dbmp = wrld.get_dbmp();
    int mark_id = dbmp.mark();
    while (!Q.empty()) {
        coords_t _c = Q.front();
        Q.pop();

        size_t _row = get_row(_c);
        size_t _col = get_col(_c);

        /* Diagonal corners */
        row_ul = MIN(_row, row_ul);
        col_ul = MIN(_col, col_ul);
        row_br = MAX(_row, row_br);
        col_br = MAX(_col, col_br);

        if (_row-1 >= 0) { // Up
            _c = get_coords(_row-1, _col);
            if (dbmp.set_visited(mark_id, CLR_TUNNEL, _c))
                Q.push(_c);
        }
        if (_row+1 < dbmp.height) { // Down
            _c = get_coords(_row+1, _col);
            if (dbmp.set_visited(mark_id, CLR_TUNNEL, _c))
                Q.push(_c);
        }
        if (_col-1 >= 0) { // Left
            _c = get_coords(_row, _col-1);
            if (dbmp.set_visited(mark_id, CLR_TUNNEL, _c))
                Q.push(_c);
        }
        if (_col+1 < dbmp.width) { // Right
            _c = get_coords(_row, _col+1);
            if (dbmp.set_visited(mark_id, CLR_TUNNEL, _c))
                Q.push(_c);
        }
    }

    dbmp.reset(mark_id);
    return {row_ul, col_ul, row_br+1, col_br+1};
}

tunnel *discover_tunnel(world &wrld, size_t row, size_t col)
{
    queue<coords_t> Q;
    coords_t _c = get_coords(row, col);
    Q.push(_c);

    auto *t = new tunnel(get_bb(wrld, _c));
    std::cout << "discover tunnel"
        << ". bb_height=" << t->box.height()
        << ", bb_width=" << t->box.width()
        << ", nbytes=" << t->dbmp.nbytes
        << std::endl;

    dbitmap &dbmp = wrld.get_dbmp();
    int mark_id = dbmp.mark();
    while (!Q.empty()) {
        _c = Q.front();
        Q.pop();
        coords_t relative_coords = sim::relativize(t->box, _c);
        t->dbmp.set(CLR_TUNNEL, relative_coords);

        size_t _row = get_row(_c);
        size_t _col = get_col(_c);

        if (_row-1 >= 0) { // Up
            _c = get_coords(_row-1, _col);
            if (dbmp.set_visited(mark_id, CLR_TUNNEL, _c))
                Q.push(_c);
        }
        if (_row+1 < dbmp.height) { // Down
            _c = get_coords(_row+1, _col);
            if (dbmp.set_visited(mark_id, CLR_TUNNEL, _c))
                Q.push(_c);
        }
        if (_col-1 >= 0) { // Left
            _c = get_coords(_row, _col-1);
            if (dbmp.set_visited(mark_id, CLR_TUNNEL, _c))
                Q.push(_c);
        }
        if (_col+1 < dbmp.width) { // Right
            _c = get_coords(_row, _col+1);
            if (dbmp.set_visited(mark_id, CLR_TUNNEL, _c))
                Q.push(_c);
        }
    }

    dbmp.reset(mark_id);
    return t;
}

/**
 * This is more C-style, we are using structs. Since
 * this is legacy, we will complete this portion of
 * code, and transform the result into a C++, OOP
 * style data structure afterwards.
 *
 * @param world
 * @param height
 * @param width
 * @param V
 * @param E
 */
void discover(world &wrld)
{
    /*
     * First, find the first tile that matches the color.
     * (0,128,0) is green which is tunnel.
     */
	size_t frame_pos = 0, row, col;
	bool found = false;
	bitmap &bmp = wrld.get_bmp();
	for (row=0; row < bmp.height; row++) {
		for (col=0; col < bmp.width; col++, frame_pos+=3) {

			/* Discover the first tile */
			if (bmp[frame_pos] == CLR_TUNNEL.r &&
                bmp[frame_pos+1] == CLR_TUNNEL.g &&
                bmp[frame_pos+2] == CLR_TUNNEL.b) {
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
	 * use this tunnel as the starting point for breadth
	 * first discovery of the entire world.
	 *
	 * Find the diagonal corners:
	 * Upper-left	: row_ul, col_ul
	 * Bottom-right	: row_br, col_br
	 */
	std::cout << "first tunnel starts: (" << row << "," << col << ")" << std::endl;
	tunnel *first_tunnel = discover_tunnel(wrld, row, col);

#ifdef DEBUG
	bb &box = first_tunnel->box;
	box.print();
	string filename = "tunnel.ppm";
	coords_t tl = get_coords(0, 0);
    coords_t br = get_coords(box.height()-1, box.width()-1);
	write_ppm(
	        filename,
	        first_tunnel->dbmp.buffer,
	        (size_t)first_tunnel->box.width(),
	        tl,
	        br,
	        (size_t)3
        );

//	delete first_tunnel;
#endif
}

void
load_world(char *input, FILE* config)
{
	unsigned char *frame_buffer = nullptr;
	unsigned int width, height;

	/* Load BMP file as bytes - each byte = 1 channel */
	loadbmp_decode_file(
	        input,
	        &frame_buffer,
	        &width,
	        &height,
	        LOADBMP_RGB);

    printf("Finished load into frame_buffer: %dx%d\n", height,width);
    assert(frame_buffer != nullptr);
	auto *wrld = new world(frame_buffer, (size_t)height, (size_t)width);
	discover(*wrld);

#ifdef DEBUG
	string filename = "discovered.ppm";
	coords_t tl = make_tuple(0, 0);
	coords_t br = make_tuple(height-1, width-1);
	write_ppm(
	        filename,
	        frame_buffer,
	        (size_t)width,
	        tl,
	        br,
	        (size_t)3);
	std::cout << "Discovered file: " << filename << std::endl;
	delete wrld;
#endif
}