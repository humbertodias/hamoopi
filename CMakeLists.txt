cmake_minimum_required(VERSION 3.7)
project(HAMOOPI)
add_executable(HAMOOPI src/HAMOOPI.c src/platform_allegro.c)

# Find Allegro
find_package(Alleg4 4)

# Add directories to the include search path
target_include_directories(HAMOOPI PRIVATE ${ALLEGRO_INCLUDE_DIR})

# Link with dependencies
target_link_libraries(HAMOOPI alleg m)

# Copy executable to parent folder after build
add_custom_command(TARGET HAMOOPI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:HAMOOPI> ${CMAKE_SOURCE_DIR}
    COMMENT "Copying executable to parent folder..."
)