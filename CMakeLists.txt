cmake_minimum_required(VERSION 3.10)
project(HAMOOPI C)

#
# Global static configuration
#
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

# Force static linking (GCC / Clang)
# Note: Commented out full -static to allow dynamic linking of system libs
# The HAMOOPI code itself is bundled statically using bundle_static_library
if (UNIX AND NOT APPLE)
    # set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
endif()

# Custom modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Include bundle_static_library function
include(bundle_static_library)

add_compile_definitions(__STATIC__=1)

# Prefer static libraries for our code, but allow shared for system libraries
# Note: CMAKE_FIND_LIBRARY_SUFFIXES controls find_library, not find_package
# SDL2 will use shared libraries (.so) if static (.a) dependencies are incomplete
set(CMAKE_FIND_FRAMEWORK NEVER)
set(CMAKE_FIND_APPBUNDLE NEVER)

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
# SDL2 (static)
#
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

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
# Bundle HAMOOPI sources into one static library
# Note: We don't link SDL2 here, only bundle our code
#
bundle_static_library(HAMOOPI_LIB HAMOOPI_BUNDLED)

#
# Create final executable
#
if (WIN32)
    add_executable(HAMOOPI WIN32 src/main.c)
else()
    add_executable(HAMOOPI src/main.c)
endif()

#
# Link bundled library and dependencies to executable
#
target_link_libraries(HAMOOPI 
    HAMOOPI_BUNDLED
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)

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
# Extra system libs for static Linux builds
#
if (APPLE)
    target_link_libraries(HAMOOPI
        "-framework CoreAudio"
        "-framework AudioToolbox"
        "-framework AudioUnit"
        "-framework CoreServices"
        "-framework Carbon"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework ForceFeedback"
        "-framework CoreVideo"
        "-framework Metal"
        "-framework CoreHaptics"  # Framework para haptic feedback
    )
endif ()

if (UNIX AND NOT APPLE)
    # Link with m pthread dl rt (standard system libraries)
    target_link_libraries(HAMOOPI
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        m
        pthread
        dl
        rt
    )
endif ()

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
