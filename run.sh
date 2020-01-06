#!/usr/bin/env bash

world_file=$1
config_file=$2

cd ../cmake-build-debug/
make clean && make
cd ..
../cmake-build-debug/sim_traffic ${world_file} ${config_file}