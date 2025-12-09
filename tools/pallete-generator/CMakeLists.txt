cmake_minimum_required(VERSION 3.10)
project(PALLETEGEN)

# Option to build Allegro version (OFF by default)
option(USE_ALLEGRO "Build Allegro 4 version instead of SDL2" OFF)

if(USE_ALLEGRO)
    # Allegro 4 Version (legacy)
    add_executable(PALLETEGEN PalleteGenerator.c)
    
    # Find Allegro
    find_package(Alleg4 4)
    
    # Add directories to the include search path
    target_include_directories(PALLETEGEN PRIVATE ${ALLEGRO_INCLUDE_DIR})
    
    # Link with dependencies
    target_link_libraries(PALLETEGEN alleg m)
else()
    # SDL2 Version (default)
    add_executable(PALLETEGEN PalleteGenerator_SDL2.c)
    
    # Use pkg-config to find SDL2 and SDL2_image
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    
    # Include directories for SDL2
    target_include_directories(PALLETEGEN PRIVATE 
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
    )
    
    # Link SDL2 libraries
    target_link_libraries(PALLETEGEN 
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
    )
    
    # Link math library on Unix-like systems
    if(UNIX)
        target_link_libraries(PALLETEGEN m)
    endif()
endif()

# Copy executable to parent folder after build
add_custom_command(TARGET PALLETEGEN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PALLETEGEN> ${CMAKE_CURRENT_SOURCE_DIR}/PALLETEGEN
    COMMENT "Copying executable to pallete-generator folder..."
)