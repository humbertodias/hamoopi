# Project
TARGET       := HAMOOPI
BUILD_DIR    := build
PLATFORM     := $(shell uname -s)-$(shell uname -m)

# Options
BUILD_TYPE   := Release
CMAKE_FLAGS  := -DCMAKE_POLICY_VERSION_MINIMUM=3.5

.PHONY: build clean zip

build:
	cmake -B $(BUILD_DIR) $(CMAKE_FLAGS) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_INSTALL_PREFIX=`pwd`/dist
	cmake --build $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TARGET).exe *.o *.so

zip:
	cmake --install build --prefix dist
	zip -r $(TARGET)-$(PLATFORM).zip dist/*