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

# Prefer static libraries (.a) over shared libraries (.so/.dylib)
# Note: If static libraries are not available, CMake will fall back to shared libraries
if(APPLE)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".dylib")
elseif(WIN32)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".lib" ".dll.a")
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".so")
endif()
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
# Note: SDL2 libraries must be linked to the final executable (not bundled)
# because bundle_static_library only bundles CMake target libraries, not
# external libraries found via find_package(). The bundled library contains
# only the HAMOOPI application code.
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
# Platform-specific system libraries
#
if (APPLE)
    # For static linking on macOS, we need additional system libraries
    # that SDL2 and its extensions depend on
    
    # Use CMake's FindBZip2 for better bzip2 detection
    find_package(BZip2)
    
    find_library(ICONV_LIB iconv)
    find_library(PNG_LIB png)
    find_library(JPEG_LIB jpeg)
    find_library(WEBP_LIB webp)
    find_library(TIFF_LIB tiff)
    find_library(ZLIB_LIB z)
    find_library(FREETYPE_LIB freetype)
    find_library(HARFBUZZ_LIB harfbuzz)
    find_library(VORBIS_LIB vorbis)
    find_library(VORBISFILE_LIB vorbisfile)
    find_library(OGG_LIB ogg)
    find_library(FLAC_LIB FLAC)
    find_library(MPG123_LIB mpg123)
    find_library(OPUS_LIB opus)
    find_library(OPUSFILE_LIB opusfile)
    find_library(MODPLUG_LIB modplug)
    find_library(XMP_LIB xmp)
    find_library(WAVPACK_LIB wavpack)
    find_library(FLUIDSYNTH_LIB fluidsynth)
    
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
        "-framework CoreHaptics"
        "-framework CoreFoundation"
        "-framework CoreGraphics"
        "-framework AppKit"
        "-framework Foundation"
        "-framework GameController"
    )
    
    # Link optional image/audio format libraries if found
    if(ICONV_LIB)
        target_link_libraries(HAMOOPI ${ICONV_LIB})
    endif()
    if(PNG_LIB)
        target_link_libraries(HAMOOPI ${PNG_LIB})
    endif()
    if(JPEG_LIB)
        target_link_libraries(HAMOOPI ${JPEG_LIB})
    endif()
    if(WEBP_LIB)
        target_link_libraries(HAMOOPI ${WEBP_LIB})
    endif()
    if(TIFF_LIB)
        target_link_libraries(HAMOOPI ${TIFF_LIB})
    endif()
    if(ZLIB_LIB)
        target_link_libraries(HAMOOPI ${ZLIB_LIB})
    endif()
    if(BZIP2_FOUND)
        target_link_libraries(HAMOOPI ${BZIP2_LIBRARIES})
    endif()
    if(FREETYPE_LIB)
        target_link_libraries(HAMOOPI ${FREETYPE_LIB})
    endif()
    if(HARFBUZZ_LIB)
        target_link_libraries(HAMOOPI ${HARFBUZZ_LIB})
    endif()
    if(VORBISFILE_LIB)
        target_link_libraries(HAMOOPI ${VORBISFILE_LIB})
    endif()
    if(VORBIS_LIB)
        target_link_libraries(HAMOOPI ${VORBIS_LIB})
    endif()
    if(OGG_LIB)
        target_link_libraries(HAMOOPI ${OGG_LIB})
    endif()
    if(FLAC_LIB)
        target_link_libraries(HAMOOPI ${FLAC_LIB})
    endif()
    if(MPG123_LIB)
        target_link_libraries(HAMOOPI ${MPG123_LIB})
    endif()
    if(OPUS_LIB)
        target_link_libraries(HAMOOPI ${OPUS_LIB})
    endif()
    if(OPUSFILE_LIB)
        target_link_libraries(HAMOOPI ${OPUSFILE_LIB})
    endif()
    if(MODPLUG_LIB)
        target_link_libraries(HAMOOPI ${MODPLUG_LIB})
    endif()
    if(XMP_LIB)
        target_link_libraries(HAMOOPI ${XMP_LIB})
    endif()
    if(WAVPACK_LIB)
        target_link_libraries(HAMOOPI ${WAVPACK_LIB})
    endif()
    if(FLUIDSYNTH_LIB)
        target_link_libraries(HAMOOPI ${FLUIDSYNTH_LIB})
    endif()
endif ()

if (UNIX AND NOT APPLE)
    # Link standard system libraries
    target_link_libraries(HAMOOPI
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
