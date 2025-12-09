cmake_minimum_required(VERSION 3.10)
project(HAMOOPI)

#
# Global static configuration
#
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)

option(USE_SDL2 "Use SDL2 backend instead of Allegro 4" OFF)

# For static build flag
add_compile_definitions(__STATIC__=1)

# Custom modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(bundle_static_library)


#
# ======================================================================
#                       INIH (STATIC LOCAL)
# ======================================================================
#
add_library(inih_static STATIC
        src/inih/ini.c
)
target_include_directories(inih_static PUBLIC src/inih)

target_compile_definitions(inih_static PUBLIC
        INI_ALLOW_MULTILINE=1
        INI_ALLOW_REALLOC=1
)

# ======================================================================
#                            SDL2 BACKEND
# ======================================================================
if(USE_SDL2)
    add_definitions(-DUSE_SDL2)

    if(WIN32)
        add_executable(HAMOOPI WIN32 src/HAMOOPI.c src/platform_sdl2.c)
    else()
        add_executable(HAMOOPI src/HAMOOPI.c src/platform_sdl2.c)
    endif()

    #
    # Find include directories
    #
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    target_include_directories(HAMOOPI PRIVATE
            ${SDL2_INCLUDE_DIRS}
            ${SDL2_IMAGE_INCLUDE_DIRS}
            ${SDL2_MIXER_INCLUDE_DIRS}
            ${SDL2_TTF_INCLUDE_DIRS}
    )

    #
    # STATIC LINKING (macOS)
    #
    if(APPLE)
        message(STATUS "Building STATIC SDL2 for macOS")

        target_link_libraries(HAMOOPI
                /opt/homebrew/lib/libSDL2.a
                /opt/homebrew/lib/libSDL2_image.a
                /opt/homebrew/lib/libSDL2_mixer.a
                /opt/homebrew/lib/libSDL2_ttf.a
                inih_static
                z
                bz2
                iconv
        )
    else()
        # Linux / Windows normal linking
        target_link_libraries(HAMOOPI
                ${SDL2_LIBRARIES}
                ${SDL2_IMAGE_LIBRARIES}
                ${SDL2_MIXER_LIBRARIES}
                ${SDL2_TTF_LIBRARIES}
                inih_static
        )
    endif()

    if(UNIX AND NOT APPLE)
        target_link_libraries(HAMOOPI m)
    endif()

    # Create libhamoopi_backend.a
    bundle_static_library(HAMOOPI hamoopi_backend)


    # ======================================================================
    #                         ALLEGRO BACKEND
    # ======================================================================
else()
    add_definitions(-DUSE_ALLEGRO4)

    if(WIN32)
        add_executable(HAMOOPI WIN32 src/HAMOOPI.c src/platform_allegro.c)
    else()
        add_executable(HAMOOPI src/HAMOOPI.c src/platform_allegro.c)
    endif()

    find_package(Allegro4 REQUIRED)

    target_include_directories(HAMOOPI PRIVATE ${ALLEGRO4_INCLUDE_DIRS})
    target_link_libraries(HAMOOPI ${ALLEGRO4_LIBRARIES})

    if(WIN32 AND MSVC)
        target_link_options(HAMOOPI PRIVATE /SAFESEH:NO)
        set_target_properties(HAMOOPI PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
    endif()

    if(UNIX)
        target_link_libraries(HAMOOPI m)
    endif()

    bundle_static_library(HAMOOPI hamoopi_backend)
endif()


# ======================================================================
#                     COPY FILES AFTER BUILD
# ======================================================================

add_custom_command(TARGET HAMOOPI POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:HAMOOPI> ${CMAKE_SOURCE_DIR}
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
