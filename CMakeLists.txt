cmake_minimum_required(VERSION 3.7)
project(HAMOOPI)
add_executable(HAMOOPI HAMOOPI.cpp allegro_compat.cpp)

# cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Add directories to the include search path
target_include_directories(HAMOOPI PRIVATE ${SDL2_INCLUDE_DIRS})

# Link with SDL2 libraries
target_link_libraries(HAMOOPI ${SDL2_LIBRARIES} SDL2_image SDL2_mixer SDL2_ttf)