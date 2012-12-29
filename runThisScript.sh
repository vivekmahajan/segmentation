#!/bin/sh
LD_LIBRARY_PATH=./usr/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH
qmake
make
./mcaq
