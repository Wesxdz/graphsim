cmake_minimum_required(VERSION 3.22)
project(GraphLifeServer)

set(CMAKE_BUILD_TYPE Debug)

# Include flecs
include_directories(deps/flecs)
include_directories(deps/enet-1.3.17/include)
add_library(flecs deps/flecs/flecs.c deps/flecs/flecs.h)
add_subdirectory(deps/enet-1.3.17)

# Create your executable
add_executable(graphsim src/main.c src/components.h)

# Link with flecs
target_link_libraries(graphsim PRIVATE flecs enet)