#include <cstdio>
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <memory>
#include <queue>
#include <set>

#include "load.h"
#include "prog.h"
#include "loadbmp.h"
#include "sim.h"
#include "world.h"
#include "BB.h"
#include "rgb.h"
#include "bitmap.h"
#include "dbitmap.h"
#include "coords_t.h"
#include "entity.h"
#include "tunnel.h"
#include "station.h"
#include "platform.h"
#include "spawn.h"

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
write_ppm(std::string &output_file,
          unsigned char *frame_buffer,
          size_t width,
          coords_t &tl,
          coords_t &br,
          size_t channels)
{
    std::cout << "writing to: " << output_file
        << ", tl=(" << tl.row << "," << tl.col << "), "
        << "br=("<< br.row << "," << br.col << "), "
        << std::endl;
	assert(channels == 1 || channels == 3);

	std::ofstream ofs;
	ofs.open(output_file);

	size_t ROW_LOWER = tl.row;
	size_t COL_LOWER = tl.col;
	size_t ROW_UPPER = br.row;
	size_t COL_UPPER = br.col;

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
	std::cout << "done" << std::endl;
}

void
write_bitmap(std::string output_file, bitmap &bmp) {
    coords_t tl = coords_t(0, 0);
    coords_t br = coords_t(bmp.height-1, bmp.width-1);
    write_ppm(output_file, bmp.buffer, bmp.width, tl, br, 3);
}

BB get_bb(world &wrld, coords_t coords, rgb &COLOR_)
{
    queue<coords_t> Q;
    Q.push(coords);

    size_t row_ul, col_ul, row_br, col_br;
    row_ul = row_br = coords.row;
    col_ul = col_br = coords.col;

    dbitmap &dbmp = wrld.get_dbmp();
    int mark_id = dbmp.mark();

    auto set = [&Q, &dbmp, &mark_id, &COLOR_]
        (coords_t coords) -> void {
            if (sim::in_bounds(coords.row, 0, dbmp.height)
                && sim::in_bounds(coords.col, 0, dbmp.width)) {
                rgb &pixel = dbmp[coords];
                if (pixel == COLOR_) {
                    dbmp.save(mark_id, pixel, coords);
                    pixel = CLR_DVISITED;
                    Q.push(coords);
                }
            }
    };

    while (!Q.empty()) {
        coords_t _c = Q.front();
        Q.pop();

        size_t _row = _c.row;
        size_t _col = _c.col;

        /* Diagonal corners */
        row_ul = MIN(_row, row_ul);
        col_ul = MIN(_col, col_ul);
        row_br = MAX(_row, row_br);
        col_br = MAX(_col, col_br);

        set(coords_t(_row-1, _col));
        set(coords_t(_row+1, _col));
        set(coords_t(_row, _col-1));
        set(coords_t(_row, _col+1));
    }

    dbmp.reset(mark_id);
    return {row_ul, col_ul, row_br+1, col_br+1};
}

entity *
recursive_discover(int mark_id,
                   world &wrld,
                   const coords_t &coords)
{
    entity *ent = nullptr;
    rgb COLOR_{};
    switch (sim::enumerate(wrld.get_dbmp()[coords])) {
        case TUNNEL:
            COLOR_ = CLR_TUNNEL;
            ent = new tunnel(get_bb(wrld, coords, COLOR_));
            break;

        case STATION:
            COLOR_ = CLR_STATION;
            ent = new station(get_bb(wrld, coords, COLOR_));
            break;

        case SPAWN_POINT:
            COLOR_ = CLR_SPAWN_POINT;
            ent = new spawn(get_bb(wrld, coords, COLOR_));
            break;

        case PLATFORM:
            COLOR_ = CLR_PLATFORM;
            ent = new platform(get_bb(wrld, coords, COLOR_));
            break;

        default:
            return nullptr;
    }

    queue<coords_t> Q;
    Q.push(coords);
    std::cout << "discover entity"
        << ". type=" << ent->name()
        << ". bb_height=" << ent->box.height()
        << ", bb_width=" << ent->box.width()
        << ", nbytes=" << ent->dbmp.nbytes
        << ", tl=" << ent->box.top_left().str()
        << ", br=" << ent->box.bot_right().str()
        << std::endl;

    auto set = [&Q, &wrld, &mark_id]
        (coords_t coords, rgb &color) -> void {
            dbitmap &dbmp = wrld.get_dbmp();
            if (sim::in_bounds(coords.row, 0, dbmp.height)
                && sim::in_bounds(coords.col, 0, dbmp.width)) {
                rgb &pixel = dbmp[coords];
                if (pixel == color) {
                    dbmp.save(mark_id, pixel, coords);
                    pixel = CLR_DCURRENT;
                    Q.push(coords);
                }
            }
    };

    // first pass: create entity
    while (!Q.empty()) {
        coords_t curr_coords = Q.front();
        Q.pop();
        coords_t relative_coords = sim::relativize(ent->box, coords);
        ent->dbmp[relative_coords] = COLOR_;

        size_t row = curr_coords.row;
        size_t col = curr_coords.col;
        set(coords_t(row-1, col), COLOR_);
        set(coords_t(row+1, col), COLOR_);
        set(coords_t(row, col-1), COLOR_);
        set(coords_t(row, col+1), COLOR_);
    }

    std::set<coords_t> unfinished;
    auto probe = [&Q, &wrld, &mark_id, &ent, &unfinished]
        (coords_t coords) -> void {
        dbitmap &dbmp = wrld.get_dbmp();
        if (sim::in_bounds(coords.row, 0, dbmp.height)
            && sim::in_bounds(coords.col, 0, dbmp.width)) {
            rgb &pixel = dbmp[coords];
            if (pixel == CLR_DCURRENT) {
                pixel = CLR_DVISITED;
                Q.push(coords);
            }

            if (pixel != CLR_DCURRENT
                && pixel != CLR_DVISITED
                && pixel != CLR_WHITE) {
                unfinished.insert(coords);
            }
        }
    };

    // second pass: discover recursive options
    Q.push(coords);
    while (!Q.empty()) {
        coords_t curr_coords = Q.front();
        Q.pop();

        size_t row = curr_coords.row;
        size_t col = curr_coords.col;
        probe(coords_t(row-1, col));
        probe(coords_t(row+1, col));
        probe(coords_t(row, col-1));
        probe(coords_t(row, col+1));
    }

    /*
     * 3rd pass to finally recursively discover. At
     * this point, the current (and all previously
     * processed entities) should be shaded
     * CLR_DVISITED, which allows the recursive
     * call to be bounded by its color.
     */
    auto it = unfinished.begin();
    for (; it != unfinished.end(); ++it) {
        coords_t coords_ = (*it);
        if (wrld.get_dbmp()[coords_] != CLR_DVISITED) {
            entity *ent_ = recursive_discover(mark_id, wrld, coords_);
            if (ent_) {
                // bi-directional link
                ent->link(ent_);
                ent_->link(ent);
            }
        }
    }

    wrld.link(ent);
    return ent;
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
    int mark_id = wrld.get_dbmp().mark();
    std::cout << "seed coords: (" << row << "," << col << ")" << std::endl;
    recursive_discover(mark_id, wrld, coords_t(row, col));
    wrld.get_dbmp().reset(mark_id);
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
    std::cout << "Discovered file: " << filename << std::endl;
	write_bitmap(filename, wrld->get_bmp());
	delete wrld;
#endif
}