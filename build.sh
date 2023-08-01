#!/bin/sh

CXX="g++"
CXXFLAGS="-O2 -Iinclude"
TARGET="fmon"
SOURCES="src/main.cpp src/util.cpp src/fmon.cpp"
OBJECTS="main.o util.o fmon.o"

$CXX $CXXFLAGS $SOURCES -c && \
$CXX $OBJECTS -o $TARGET && \
./$TARGET $@
