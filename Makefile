# i was up all night on adderall writing this dont judge

### --- variables ---
CXX=g++
CXXFLAGS=-O2 -Iinclude
TARGET=fmon
TARGETEXT=
SOURCES=src/main.cpp src/util.cpp src/fmon.cpp
OBJECTS=main.o util.o fmon.o
LIB=lib$(TARGET)
LIBEXT=

# $(PLATFORM) can either be
# false: no custom platform; default
# windows: use windows
# unix: use unix
PLATFORM=false

ifeq ($(PLATFORM),false)
ifeq ($(OS),Windows_NT)
	PLATFORM=windows
else
	PLATFORM=unix
endif
endif

ifeq ($(PLATFORM), windows)
	TARGETEXT=.exe
	LIBEXT=.dll

ifneq ($(OS),Windows_NT)
	CXX=x86_64-w64-mingw32-g++
endif
endif
ifeq ($(PLATFORM), unix)
	LIBEXT=.so
endif

### --- default targets ---
all: $(TARGET)

### --- main `fmon` program ---
build: $(SOURCES)
	$(CXX) $(CFLAGS) $(CXXFLAGS) $^ -c

$(TARGET): build
	$(CXX) $(CFLAGS) $(OBJECTS) -o $(TARGET)$(TARGETEXT)

# run as root
install: $(TARGET)
ifeq ($(PLATFORM),unix)
ifneq ($(OS),Windows_NT)
	cp $(TARGET)$(TARGETEXT) /usr/bin
else
	@echo "cannot install unix fmon to windows"
	$(MAKE) clean
endif
endif
ifeq ($(PLATFORM),windows)
ifeq ($(OS),Windows_NT)
	cp $(TARGET)$(TARGETEXT) C:\Windows
else
	@echo "cannot install windows fmon to unix"
	$(MAKE) clean
endif
endif

# run as root
uninstall:
ifeq ($(PLATFORM),unix)
ifneq ($(OS),Windows_NT)
	rm -f /usr/bin/$(TARGET)$(TARGETEXT)
else
	@echo "cannot uninstall unix fmon from windows"
	$(MAKE) clean
endif
endif
ifeq ($(PLATFORM),windows)
ifeq ($(OS),Windows_NT)
	rd /s /q C:\Windows\$(TARGET)$(TARGETEXT)
else
	@echo "cannot uninstall windows fmon from unix"
	$(MAKE) clean
endif
endif

### --- main `fmon` api library
build-lib: src/fmon.cpp
	$(CXX) $(CXXFLAGS) $^ -fPIC -c

lib: build-lib
	$(CXX) fmon.o -shared -o $(LIB)$(LIBEXT)

# run as root
lib-install: lib
ifeq ($(PLATFORM),unix)
ifneq ($(OS),Windows_NT)
	cp include/fmon.h /usr/include
	cp $(LIB)$(LIBEXT) /usr/lib
else
	@echo "cannot install unix fmon library to windows"
	$(MAKE) clean
endif
endif
ifeq ($(PLATFORM),windows)
ifeq ($(OS),Windows_NT)
	@echo "to include fmon.h you need to copy include/fmon.h to your project source directory"
	cp $(LIB)$(LIBEXT) C:\Windows
else
	@echo "cannot install windows fmon library to unix"
	$(MAKE) clean
endif
endif

# run as root
lib-uninstall:
ifeq ($(PLATFORM),unix)
ifneq ($(OS),Windows_NT)
	rm -f /usr/include/fmon.h /usr/lib/$(LIB)$(LIBEXT)
else
	@echo "cannot uninstall unix fmon library from windows"
	$(MAKE) clean
endif
endif
ifeq ($(PLATFORM),windows)
ifeq ($(OS),Windows_NT)
	rd /s /q C:\system32\$(LIB)$(LIBEXT)
else
	@echo "cannot uninstall windows fmon library from unix"
	$(MAKE) clean
endif
endif

clean:
	rm -f $(OBJECTS) $(TARGET) $(TARGET).exe $(LIB).so $(LIB).dll
