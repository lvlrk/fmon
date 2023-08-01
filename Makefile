### --- variables ---
CXX=g++
CXXFLAGS=-O2 -Iinclude
TARGET=fmon
TARGET32=fmon32
SOURCES=src/main.cpp src/util.cpp src/fmon.cpp
OBJECTS=main.o util.o fmon.o
LIB=libfmon.so
LIB32=libfmon32.so

### --- default targets ---
all: $(TARGET)
all32: $(TARGET32)

### --- main `fmon` program ---
build: $(SOURCES)
	$(CXX) $(CFLAGS) $(CXXFLAGS) $^ -c

$(TARGET): build
	$(CXX) $(CFLAGS) $(OBJECTS) -o $(TARGET)

# run as root
install: $(TARGET)
	cp $(TARGET) /usr/bin

# run as root
uninstall:
	rm -f /usr/bin/$(TARGET)

### --- 32-bit `fmon` program ---
build32: $(SOURCES)
	$(CXX) $(CFLAGS) $(CXXFLAGS) $^ -c -m32

$(TARGET32): build32
	$(CXX) $(CFLAGS) $(OBJECTS) -o $(TARGET32) -m32

# run as root
install32: $(TARGET32)
	cp $(TARGET32) /usr/bin

# run as root
uninstall32:
	rm -f /usr/bin/$(TARGET32)

### --- main `fmon` api library
build-lib: src/fmon.cpp
	$(CXX) $(CXXFLAGS) $^ -fPIC -c

lib: build-lib
	$(CXX) fmon.o -shared -o $(LIB)

# run as root
lib-install: lib
	cp include/fmon.h /usr/include
	cp $(LIB) /usr/lib

# run as root
lib-uninstall:
	rm -f /usr/include/fmon.h /usr/lib/$(LIB)

### --- 32-bit `fmon` api library
build-lib32: src/fmon.cpp
	$(CXX) $(CXXFLAGS) $^ -fPIC -c -m32

lib32: build-lib32
	$(CXX) fmon.o -shared -o $(LIB32) -m32

# run as root
lib-install32: lib32
	cp include/fmon.h /usr/include
	cp $(LIB32) /usr/lib

# run as root
lib-uninstall32:
	rm -f /usr/include/fmon.h /usr/lib/$(LIB32)

clean:
	rm -f $(OBJECTS) $(TARGET) $(TARGET32) $(LIB) $(LIB32)

.PHONY: clean
