cmake_minimum_required(VERSION 3.14)
project(HAMOOPI VERSION 1.0.0 LANGUAGES C)
set(EXECUTABLE_NAME "HAMOOPI")
set(ICON_NAME "hamoopi")

option(STEAMDECK "Build specifically for Steam Deck (SteamOS)" OFF)

# --- Detect Nintendo Switch build ---
if(CMAKE_TOOLCHAIN_FILE AND CMAKE_TOOLCHAIN_FILE MATCHES "Switch.cmake")
    set(NINTENDO_SWITCH TRUE)
    message(STATUS "🎮 Configuring build for Nintendo Switch")
else()
    set(NINTENDO_SWITCH FALSE)
endif()

# --- Validação ---
if(STEAMDECK AND (NOT UNIX OR APPLE))
    message(FATAL_ERROR "STEAMDECK build is only supported on Linux (SteamOS)")
endif()

# --- Global static configuration ---
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)
set(CMAKE_FIND_FRAMEWORK NEVER)
set(CMAKE_FIND_APPBUNDLE NEVER)

# --- Steam Deck global flags ---
if(STEAMDECK)
    message(STATUS "🟢 Configuring build for Steam Deck")

    set(CMAKE_C_STANDARD 99)
    set(CMAKE_BUILD_TYPE Release)

    # Steam Deck CPU (Zen 2)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -march=znver2 -mtune=znver2 -fno-plt")

    # Nunca gerar binário totalmente estático
    set(CMAKE_EXE_LINKER_FLAGS "")

    add_compile_definitions(STEAMDECK LINUX)
endif()

include(FetchContent)

# --- Nintendo Switch: Use system libraries from devkitPro ---
if(NINTENDO_SWITCH)
    # Switch uses libraries from portlibs, not FetchContent
    # Skip bzip2, zlib, libpng, SDL2 FetchContent for Switch builds
    message(STATUS "Using devkitPro portlibs for Nintendo Switch")
    
    # SDL2 and other libraries are provided by switch-dev package
    find_package(PkgConfig REQUIRED)
    
    # The toolchain should set up paths to find SDL2 libraries
    set(SDL_STATIC ON CACHE BOOL "" FORCE)
    set(SDL_SHARED OFF CACHE BOOL "" FORCE)
    
else()
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
            GIT_TAG v1.3.1.2
    )
    FetchContent_MakeAvailable(zlib)

    if(TARGET zlibstatic AND NOT TARGET ZLIB::ZLIB)
        add_library(ZLIB::ZLIB ALIAS zlibstatic)
    endif()

    # --- libpng ---
    set(PNG_SHARED OFF CACHE BOOL "" FORCE)
    set(PNG_STATIC ON CACHE BOOL "" FORCE)
    set(PNG_FRAMEWORK OFF CACHE BOOL "" FORCE)
    set(PNG_TESTS OFF CACHE BOOL "" FORCE)
    set(PNG_INSTALL OFF CACHE BOOL "" FORCE)
    set(PNG_SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE)
    set(SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE)
    set(PNG_ZLIB_VERSION "internal" CACHE STRING "" FORCE)
    set(ZLIB_ROOT "${zlib_SOURCE_DIR}" CACHE PATH "" FORCE)
    set(ZLIB_LIBRARY zlib CACHE FILEPATH "" FORCE)
    set(ZLIB_INCLUDE_DIR ${zlib_SOURCE_DIR} CACHE PATH "" FORCE)
    set(ZLIB_BUILD_TESTING OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
            libpng
            GIT_REPOSITORY https://github.com/glennrp/libpng.git
            GIT_TAG v1.6.53
    )
    FetchContent_MakeAvailable(libpng)
endif()

if(STEAMDECK)
    # SDL estático, áudio dinâmico (CORRETO)
    set(SDL_AUDIO_DRIVER_PIPEWIRE OFF CACHE BOOL "" FORCE)
    set(SDL_AUDIO_DRIVER_PULSEAUDIO OFF CACHE BOOL "" FORCE)
    set(SDL_AUDIO_DRIVER_ALSA OFF CACHE BOOL "" FORCE)

    set(SDL_VIDEO_WAYLAND ON CACHE BOOL "" FORCE)
    set(SDL_VIDEO_X11 ON CACHE BOOL "" FORCE)

    set(SDL_HIDAPI_JOYSTICK ON CACHE BOOL "" FORCE)
endif()

if(NOT NINTENDO_SWITCH)
    set(SDL_STATIC ON CACHE BOOL "" FORCE)
    set(SDL_SHARED OFF CACHE BOOL "" FORCE)
    set(SDL_TEST OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(SDL2 GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG release-2.32.10 GIT_SHALLOW TRUE)
    FetchContent_Declare(SDL2_image GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git GIT_TAG release-2.8.8 GIT_SHALLOW TRUE)
    FetchContent_Declare(SDL2_mixer GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git GIT_TAG release-2.8.1 GIT_SHALLOW TRUE)
    FetchContent_Declare(SDL2_ttf GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git GIT_TAG release-2.24.0 GIT_SHALLOW TRUE)

    set(SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_DEPS_SHARED OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_VENDORED ON CACHE BOOL "" FORCE)

    set(SDL2MIXER_INSTALL OFF CACHE BOOL "" FORCE)
    set(SDL2MIXER_DEPS_SHARED OFF CACHE BOOL "" FORCE)
    set(SDL2MIXER_VENDORED ON CACHE BOOL "" FORCE)
    set(SDL2MIXER_MIDI ON CACHE BOOL "" FORCE)
    set(SDL2MIXER_WAVE ON CACHE BOOL "" FORCE)
    # Audio backends (Linux)
    if(UNIX AND NOT APPLE)
        set(SDL_AUDIO_DRIVER_ALSA ON CACHE BOOL "" FORCE)
        set(SDL_AUDIO_DRIVER_PULSEAUDIO ON CACHE BOOL "" FORCE)
        set(SDL_AUDIO_DRIVER_PIPEWIRE ON CACHE BOOL "" FORCE)

        set(SDL_VIDEO_X11 ON CACHE BOOL "" FORCE)
        set(SDL_VIDEO_WAYLAND ON CACHE BOOL "" FORCE)
    endif()

    set(SDL2TTF_INSTALL OFF CACHE BOOL "" FORCE)
    set(SDL2TTF_VENDORED ON CACHE BOOL "" FORCE)
    # Disable AVIF / dav1d (avoids NASM dependency)
    set(SDL2IMAGE_AVIF OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_VENDORED_DAV1D OFF CACHE BOOL "" FORCE)
    # Disable TIFF support (avoids libtiff.so dependency)
    set(SDL2IMAGE_TIF OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_TIFF OFF CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_mixer SDL2_ttf)

    # --- Includes ---
    set(SDL2_INCLUDE_DIRS "./build/_deps/sdl2-src/include")
    set(SDL2_IMAGE_INCLUDE_DIRS "./build/_deps/sdl2_image-src/include")
    set(SDL2_MIXER_INCLUDE_DIRS "./build/_deps/sdl2_mixer-src/include")
    get_target_property(_SDL2_TTF_INCLUDES SDL2_ttf::SDL2_ttf-static INTERFACE_INCLUDE_DIRECTORIES)
    set(SDL2_TTF_INCLUDE_DIRS ${_SDL2_TTF_INCLUDES})
else()
    # Nintendo Switch: Find SDL2 from portlibs
    find_package(SDL2 QUIET)
    find_package(SDL2_image QUIET)
    find_package(SDL2_mixer QUIET)
    find_package(SDL2_ttf QUIET)
    
    if(NOT SDL2_FOUND)
        message(FATAL_ERROR "SDL2 not found. Please ensure devkitPro portlibs are installed (switch-dev package).")
    endif()
    if(NOT SDL2_image_FOUND)
        message(FATAL_ERROR "SDL2_image not found. Please ensure devkitPro portlibs are installed (switch-dev package).")
    endif()
    if(NOT SDL2_mixer_FOUND)
        message(FATAL_ERROR "SDL2_mixer not found. Please ensure devkitPro portlibs are installed (switch-dev package).")
    endif()
    if(NOT SDL2_ttf_FOUND)
        message(FATAL_ERROR "SDL2_ttf not found. Please ensure devkitPro portlibs are installed (switch-dev package).")
    endif()
    
    # Set include directories from found packages
    # Handle both singular and plural forms returned by different FindSDL2 modules
    if(NOT SDL2_INCLUDE_DIRS AND SDL2_INCLUDE_DIR)
        set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})
    endif()
    
    if(NOT SDL2_IMAGE_INCLUDE_DIRS AND SDL2_IMAGE_INCLUDE_DIR)
        set(SDL2_IMAGE_INCLUDE_DIRS ${SDL2_IMAGE_INCLUDE_DIR})
    endif()
    
    if(NOT SDL2_MIXER_INCLUDE_DIRS AND SDL2_MIXER_INCLUDE_DIR)
        set(SDL2_MIXER_INCLUDE_DIRS ${SDL2_MIXER_INCLUDE_DIR})
    endif()
    
    if(NOT SDL2_TTF_INCLUDE_DIRS AND SDL2_TTF_INCLUDE_DIR)
        set(SDL2_TTF_INCLUDE_DIRS ${SDL2_TTF_INCLUDE_DIR})
    endif()
endif()

# --- Biblioteca ---
add_library(HAMOOPI_LIB STATIC
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

target_include_directories(HAMOOPI_LIB PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/src/backend/minini
)

# --- Executável ---
add_executable(HAMOOPI src/main.c)

if(WIN32)
    target_compile_definitions(HAMOOPI PRIVATE SDL_MAIN_HANDLED)
endif()

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
)

# Platform-specific linking
if(NINTENDO_SWITCH)
    # Nintendo Switch uses libraries from portlibs
    target_link_libraries(HAMOOPI
            ${SDL2_LIBRARY}
            ${SDL2_IMAGE_LIBRARIES}
            ${SDL2_MIXER_LIBRARIES}
            ${SDL2_TTF_LIBRARIES}
    )
else()
    # Other platforms use static SDL2 from FetchContent
    target_link_libraries(HAMOOPI
            SDL2::SDL2-static
            SDL2_image::SDL2_image-static
            SDL2_mixer::SDL2_mixer-static
            SDL2_ttf::SDL2_ttf-static
            png_static
            zlibstatic
    )
endif()

# --- Steam Deck: runtime-safe link + RPATH ---
if(STEAMDECK)
    target_link_libraries(HAMOOPI
            m
            dl
            pthread
            rt
    )

    set_target_properties(HAMOOPI PROPERTIES
            BUILD_WITH_INSTALL_RPATH TRUE
            INSTALL_RPATH "$ORIGIN"
    )
endif()

if(UNIX AND NOT APPLE AND NOT NINTENDO_SWITCH)
    target_link_libraries(HAMOOPI
            asound
    )
endif()

# --- Nintendo Switch specific configuration ---
if(NINTENDO_SWITCH)
    # Set output to NRO format for Switch homebrew
    set_target_properties(HAMOOPI PROPERTIES
            SUFFIX ".elf"
    )
    
    # Get DEVKITPRO path from environment or use default
    if(DEFINED ENV{DEVKITPRO})
        set(DEVKITPRO_PATH $ENV{DEVKITPRO})
    else()
        set(DEVKITPRO_PATH "/opt/devkitpro")
    endif()
    
    # Create NACP file (Nintendo Switch metadata)
    add_custom_command(TARGET HAMOOPI PRE_LINK
            COMMAND nacptool --create "HAMOOPI" "humbertodias" "${PROJECT_VERSION}" ${CMAKE_BINARY_DIR}/HAMOOPI.nacp
            COMMENT "Creating NACP metadata for Nintendo Switch"
    )
    
    # Create NRO file using elf2nro
    add_custom_command(TARGET HAMOOPI POST_BUILD
            COMMAND elf2nro $<TARGET_FILE:HAMOOPI> ${CMAKE_BINARY_DIR}/HAMOOPI.nro
            --icon=${CMAKE_SOURCE_DIR}/data/system/hamoopi_logo.png
            --nacp=${CMAKE_BINARY_DIR}/HAMOOPI.nacp
            COMMENT "Converting ELF to NRO format for Nintendo Switch"
    )
endif()

# --- Includes ---
target_include_directories(HAMOOPI PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/src/backend/minini
)

if(UNIX AND NOT APPLE AND NOT NINTENDO_SWITCH)
    install(FILES data/system/hamoopi_logo.png DESTINATION .)
    install(FILES ${CMAKE_BINARY_DIR}/hamoopi.desktop DESTINATION .)
    configure_file(
            ${CMAKE_SOURCE_DIR}/cmake/hamoopi.desktop.in
            ${CMAKE_BINARY_DIR}/hamoopi.desktop
            @ONLY
    )
endif()

if(NINTENDO_SWITCH)
    # Install NRO file for Switch
    install(FILES ${CMAKE_BINARY_DIR}/HAMOOPI.nro DESTINATION .)
else()
    install(TARGETS HAMOOPI RUNTIME DESTINATION .)
endif()

install(DIRECTORY data DESTINATION .)
install(FILES SETUP.ini README.md LICENSE DESTINATION .)