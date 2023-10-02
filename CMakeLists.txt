cmake_minimum_required(VERSION 3.22)
project(GraphLifeServer)

# Include flecs
include_directories(deps/flecs)
add_library(flecs deps/flecs/flecs.c deps/flecs/flecs.h)

# Create your executable
add_executable(graphs src/main.c)

# Link with flecs
target_link_libraries(graphs PRIVATE flecs)
