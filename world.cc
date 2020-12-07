#include <cstdio>

#include <queue>

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

void world::copy_from(entity &entity) {
    BB &ent_box = entity.box;
    dbitmap &ent_dbmp = entity.dbmp;
    coords_t initial_coords{};
    bool found = false;
    for (int row = 0; row < ent_box.height(); ++row) {
        for (int col = 0; col < ent_box.width(); ++col) {
            coords_t coords = coords_t(row, col);
            if (ent_dbmp[coords] != CLR_WHITE) {
                initial_coords = coords;
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }

    if (!found) {
        return;
    }

    std::queue<coords_t> Q;
    Q.push(initial_coords);
    int mark_id = ent_dbmp.mark();

    /*
     * Sets world bitmap pixel to whatever color was
     * in the entity bitmap - Need to make entity
     * bitmap coords absolute.
     */
    dbitmap &this_dbmp = dbmp;
    auto set = [&ent_box, &ent_dbmp, &this_dbmp, &mark_id, &Q]
        (coords_t coords) -> void {
            if (sim::in_bounds(coords.row, 0, ent_box.height())
                && sim::in_bounds(coords.col, 0, ent_box.width())) {
                rgb &pixel = ent_dbmp[coords];
                if (pixel != CLR_WHITE) {
                    coords_t abs_coords = sim::absolute(ent_box, coords);
                    this_dbmp[abs_coords] = pixel;

                    ent_dbmp.save(mark_id, pixel, coords);
                    ent_dbmp[coords] = CLR_DVISITED;
                    Q.push(coords);
                }
            }
    };

    while (!Q.empty()) {
        coords_t &coords = Q.front();
        Q.pop();

        size_t row = coords.row;
        size_t col = coords.col;
        set(coords_t(row-1, col));
        set(coords_t(row+1, col));
        set(coords_t(row, col-1));
        set(coords_t(row, col+1));
    }

    ent_dbmp.reset(mark_id);
}

void world::calibrate() {
    /*
     * For each platform, compute the shortest path
     * to all other platforms; cache only the next
     * hop one would take to reach their destination,
     * as well as the weight of the complete shortest
     * path.
     *
     * This for use during the simulation.
     */
}
