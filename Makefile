# Default build type
BUILD_TYPE ?= Debug

# Build directory
BUILD_DIR = build

# CMake generator (Ninja by default, but can be overridden)
CMAKE_GENERATOR ?= Ninja

# Default target
all: build

# Create build directory and run CMake
$(BUILD_DIR)/build.ninja:
	mkdir -p $(BUILD_DIR)
	cmake -B $(BUILD_DIR) -G $(CMAKE_GENERATOR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

# Build the project
build: $(BUILD_DIR)/build.ninja
	cd $(BUILD_DIR) && cmake --build .

# Run the game
run: build
	cd $(BUILD_DIR) && ./dungeon_loop

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

# Rebuild everything from scratch
rebuild: clean all

.PHONY: all build run clean rebuild
