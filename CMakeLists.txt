cmake_minimum_required(VERSION 3.7)
project(HAMOOPI C)

# Option to choose backend
option(USE_STB_BACKEND "Use STB backend instead of Allegro" OFF)

if(USE_STB_BACKEND)
    message(STATUS "Building with STB backend")
    
    # Add STB backend sources
    add_executable(HAMOOPI 
        src/HAMOOPI.cpp 
        src/hamoopi_c_backend_stb.c
    )
    
    # Add STB-specific definitions
    target_compile_definitions(HAMOOPI PRIVATE USE_STB_BACKEND)
    
    # Link with math library (required by STB)
    target_link_libraries(HAMOOPI m)
    
else()
    message(STATUS "Building with Allegro backend (default)")
    
    # Add Allegro backend sources - now using unified C backend
    add_executable(HAMOOPI 
        src/HAMOOPI.cpp 
        src/hamoopi_c_backend_allegro.c
    )
    
    # Find Allegro
    find_package(Alleg4 4)
    
    # Add directories to the include search path
    target_include_directories(HAMOOPI PRIVATE ${ALLEGRO_INCLUDE_DIR})
    
    # Link with dependencies
    target_link_libraries(HAMOOPI alleg)
endif()

# Common include directories
target_include_directories(HAMOOPI PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Use C compiler for .cpp files (actually pure C)
set_source_files_properties(src/HAMOOPI.cpp PROPERTIES LANGUAGE C)