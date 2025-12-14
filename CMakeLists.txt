cmake_minimum_required(VERSION 3.14) # FetchContent requires 3.14+
project(HAMOOPI C)

#
# Global static configuration
#
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

# Prefer static libraries (.a) over shared libraries (.so/.dylib)
# Note: If static libraries are not available, CMake will fall back to shared libraries
set(CMAKE_FIND_FRAMEWORK NEVER)
set(CMAKE_FIND_APPBUNDLE NEVER)

message(STATUS "Building SDL2 and dependencies from source...")
include(FetchContent)

# bzip2
FetchContent_Declare(
    bzip2
    GIT_REPOSITORY https://sourceware.org/git/bzip2.git
    GIT_TAG bzip2-1.0.8
)
FetchContent_MakeAvailable(bzip2)

set(ZLIB_BUILD_SHARED OFF CACHE BOOL "Build shared zlib" FORCE)
set(ZLIB_BUILD_STATIC ON CACHE BOOL "Build static zlib" FORCE)

FetchContent_Declare(
    zlib
    GIT_REPOSITORY https://github.com/madler/zlib.git
    GIT_TAG v1.3.1
)
FetchContent_MakeAvailable(zlib)

# libpng
set(PNG_SHARED OFF CACHE BOOL "" FORCE)
set(PNG_STATIC ON CACHE BOOL "" FORCE)
set(PNG_FRAMEWORK OFF CACHE BOOL "" FORCE)
set(PNG_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    libpng
    GIT_REPOSITORY https://github.com/glennrp/libpng.git
    GIT_TAG v1.6.43
)


FetchContent_MakeAvailable(libpng)

set(SDL_PIPEWIRE OFF CACHE BOOL "" FORCE)

# SDL2
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.10
    GIT_SHALLOW TRUE
)

# SDL2_image
FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.3
    GIT_SHALLOW TRUE
)

# SDL2_mixer
FetchContent_Declare(
    SDL2_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG release-2.8.1
    GIT_SHALLOW TRUE
)

# SDL2_ttf
FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.24.0
    GIT_SHALLOW TRUE
)

# Configure SDL2 options
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)

# Configure SDL2_image options
set(SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_DEPS_SHARED OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_VENDORED ON CACHE BOOL "" FORCE)

# Configure SDL2_mixer options
set(SDL2MIXER_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_DEPS_SHARED OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_VENDORED ON CACHE BOOL "" FORCE)

# Configure SDL2_ttf options
set(SDL2TTF_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2TTF_VENDORED ON CACHE BOOL "" FORCE)

# Make SDL2 and extensions available
FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_mixer SDL2_ttf)

# Set variables for later use
# Note: FetchContent creates targets with proper include directories
if(TARGET SDL2::SDL2-static)
    set(SDL2_LIBRARIES SDL2::SDL2-static)
    # Get include directories from the target
    get_target_property(_SDL2_INCLUDES SDL2::SDL2-static INTERFACE_INCLUDE_DIRECTORIES)
    set(SDL2_INCLUDE_DIRS "./build/_deps/sdl2-src/include")
endif()
if(TARGET SDL2_image::SDL2_image-static)
    set(SDL2_IMAGE_LIBRARIES SDL2_image::SDL2_image-static)
    get_target_property(_SDL2_IMAGE_INCLUDES SDL2_image::SDL2_image-static INTERFACE_INCLUDE_DIRECTORIES)
    if(_SDL2_IMAGE_INCLUDES)
        set(SDL2_IMAGE_INCLUDE_DIRS ${_SDL2_IMAGE_INCLUDES})
    endif()
endif()
if(TARGET SDL2_mixer::SDL2_mixer-static)
    set(SDL2_MIXER_LIBRARIES SDL2_mixer::SDL2_mixer-static)
    get_target_property(_SDL2_MIXER_INCLUDES SDL2_mixer::SDL2_mixer-static INTERFACE_INCLUDE_DIRECTORIES)
    if(_SDL2_MIXER_INCLUDES)
        set(SDL2_MIXER_INCLUDE_DIRS ${_SDL2_MIXER_INCLUDES})
    endif()
endif()
if(TARGET SDL2_ttf::SDL2_ttf-static)
    set(SDL2_TTF_LIBRARIES SDL2_ttf::SDL2_ttf-static)
    get_target_property(_SDL2_TTF_INCLUDES SDL2_ttf::SDL2_ttf-static INTERFACE_INCLUDE_DIRECTORIES)
    if(_SDL2_TTF_INCLUDES)
        set(SDL2_TTF_INCLUDE_DIRS ${_SDL2_TTF_INCLUDES})
    endif()
endif()

#
# Create static library with HAMOOPI sources
#
set(HAMOOPI_SOURCES
    src/modules/input.c
    src/modules/collision.c
    src/modules/player.c
    src/modules/editor.c
    src/game_loop/donation.c
    src/game_loop/intro.c
    src/game_loop/presentation.c
    src/game_loop/play.c
    src/game_loop/stage_select.c
    src/game_loop/char_select.c
    src/game_loop/options.c
    src/game_loop/versus.c
    src/game_loop/edit.c
    src/backend/platform_sdl2.c
    src/backend/minini/minIni.c
)

add_library(HAMOOPI_LIB STATIC ${HAMOOPI_SOURCES})

#
# Includes for HAMOOPI_LIB
#
target_include_directories(HAMOOPI_LIB PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src/backend/minini
)

#
# Create final executable
#
if(WIN32)
    add_executable(HAMOOPI WIN32 src/main.c)
else()
    add_executable(HAMOOPI src/main.c)
endif()


target_link_libraries(HAMOOPI
    HAMOOPI_LIB

    SDL2::SDL2-static
    SDL2_image::SDL2_image-static
    SDL2_mixer::SDL2_mixer-static
    SDL2_ttf::SDL2_ttf-static

    png_static
    zlibstatic
)

if(APPLE)
    target_link_libraries(HAMOOPI
        "-framework CoreFoundation"
        "-framework Foundation"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework ForceFeedback"
        "-framework GameController"
        "-framework CoreHaptics"
        "-framework CoreAudio"
        "-framework AudioToolbox"
        "-framework AudioUnit"
        "-framework CoreVideo"
        "-framework CoreGraphics"
        "-framework Metal"
        "-framework AppKit"
    )
endif()

#
# Include directories for executable
#
target_include_directories(HAMOOPI PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src/backend/minini
)


#
# Post-build assets
#
add_custom_command(TARGET HAMOOPI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:HAMOOPI> ${CMAKE_SOURCE_DIR}
    COMMENT "Copying executable to parent folder..."
)

add_custom_command(TARGET HAMOOPI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data
    $<TARGET_FILE_DIR:HAMOOPI>/data
)

add_custom_command(TARGET HAMOOPI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/SETUP.ini
    $<TARGET_FILE_DIR:HAMOOPI>/SETUP.ini
)
