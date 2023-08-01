#!/bin/sh

CXX="g++"
CXXFLAGS="-O2 -Iinclude"
TARGET="libfmon.so"
SOURCES="src/fmon.cpp"
OBJECTS="fmon.o"

cp include/fmon.h /usr/include
$CXX $CXXFLAGS $SOURCES -c -fPIC && \
$CXX $OBJECTS -shared -o $TARGET && \
cp $TARGET /usr/lib
