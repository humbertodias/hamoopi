cmake_minimum_required(VERSION 3.14)
project(HAMOOPI C)

# --- Global static configuration ---
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)
set(CMAKE_FIND_FRAMEWORK NEVER)
set(CMAKE_FIND_APPBUNDLE NEVER)

include(FetchContent)

# --- bzip2 ---
FetchContent_Declare(
    bzip2
    GIT_REPOSITORY https://sourceware.org/git/bzip2.git
    GIT_TAG bzip2-1.0.8
)
FetchContent_MakeAvailable(bzip2)

# --- zlib ---
set(ZLIB_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(ZLIB_BUILD_STATIC ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    zlib
    GIT_REPOSITORY https://github.com/madler/zlib.git
    GIT_TAG v1.3.1
)
FetchContent_MakeAvailable(zlib)

# Cria alias ZLIB::ZLIB se não existir
if(TARGET zlibstatic AND NOT TARGET ZLIB::ZLIB)
    add_library(ZLIB::ZLIB ALIAS zlibstatic)
endif()

# --- libpng ---
set(PNG_SHARED OFF CACHE BOOL "" FORCE)
set(PNG_STATIC ON CACHE BOOL "" FORCE)
set(PNG_FRAMEWORK OFF CACHE BOOL "" FORCE)
set(PNG_TESTS OFF CACHE BOOL "" FORCE)
set(PNG_INSTALL OFF CACHE BOOL "" FORCE) # evita export/install problemático
# 🔴 ESSAS DUAS são as que realmente resolvem
set(PNG_SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE)
set(SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE)
set(PNG_ZLIB_VERSION "internal" CACHE STRING "" FORCE)
set(ZLIB_ROOT "${zlib_SOURCE_DIR}" CACHE PATH "" FORCE)
# --- ZLIB for libpng (Windows fix) ---
set(ZLIB_LIBRARY zlib CACHE FILEPATH "" FORCE)
set(ZLIB_INCLUDE_DIR ${zlib_SOURCE_DIR} CACHE PATH "" FORCE)
FetchContent_Declare(
    libpng
    GIT_REPOSITORY https://github.com/glennrp/libpng.git
    GIT_TAG v1.6.43
)
FetchContent_MakeAvailable(libpng)

# --- SDL2 e extensões ---
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)

FetchContent_Declare(SDL2 GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG release-2.30.10 GIT_SHALLOW TRUE)
FetchContent_Declare(SDL2_image GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git GIT_TAG release-2.8.3 GIT_SHALLOW TRUE)
FetchContent_Declare(SDL2_mixer GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git GIT_TAG release-2.8.1 GIT_SHALLOW TRUE)
FetchContent_Declare(SDL2_ttf GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git GIT_TAG release-2.24.0 GIT_SHALLOW TRUE)

# Configurações das dependências SDL2
set(SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_DEPS_SHARED OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_VENDORED ON CACHE BOOL "" FORCE)

set(SDL2MIXER_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_DEPS_SHARED OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_VENDORED ON CACHE BOOL "" FORCE)

set(SDL2TTF_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2TTF_VENDORED ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_mixer SDL2_ttf)

# --- Variáveis de include ---
set(SDL2_INCLUDE_DIRS "./build/_deps/sdl2-src/include")
set(SDL2_IMAGE_INCLUDE_DIRS "./build/_deps/sdl2_image-src/include")
set(SDL2_MIXER_INCLUDE_DIRS "./build/_deps/sdl2_mixer-src/include")

get_target_property(_SDL2_TTF_INCLUDES SDL2_ttf::SDL2_ttf-static INTERFACE_INCLUDE_DIRECTORIES)
set(SDL2_TTF_INCLUDE_DIRS ${_SDL2_TTF_INCLUDES})

# --- Biblioteca HAMOOPI ---
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
target_include_directories(HAMOOPI_LIB PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src/backend/minini
)

# --- Executável ---
if(WIN32)
    add_executable(HAMOOPI WIN32 src/main.c)
else()
    add_executable(HAMOOPI src/main.c)
endif()

if(WIN32)
    target_compile_definitions(HAMOOPI PRIVATE SDL_MAIN_HANDLED)
endif(

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

target_link_libraries(HAMOOPI
    HAMOOPI_LIB
    SDL2::SDL2-static
    SDL2_image::SDL2_image-static
    SDL2_mixer::SDL2_mixer-static
    SDL2_ttf::SDL2_ttf-static
    png_static
    zlibstatic
)

# --- Includes para o executável ---
target_include_directories(HAMOOPI PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src/backend/minini
)

install(TARGETS HAMOOPI RUNTIME DESTINATION .)
install(DIRECTORY data DESTINATION .)
install(FILES SETUP.ini README.md LICENSE DESTINATION .)
