cmake_minimum_required(VERSION 3.10)
project(sim_traffic)

set(CMAKE_CXX_STANDARD 14)

add_executable(sim_traffic
        sim.cc
        load.h load.cc loadbmp.h sim.h world.h world.cc tunnel.cpp tunnel.h bb.cpp bb.h rgb.cpp rgb.h bitmap.cpp bitmap.h dbitmap.cpp dbitmap.h prog.h coords_t.h)
