cmake_minimum_required(VERSION 3.10)
project(Simulation)

set(CMAKE_CXX_STANDARD 20)
include_directories(include)

set(SOURCES
    src/main.cpp
    src/Body.cpp
    src/verletIntegrator.cpp
    src/vector2D.cpp
    src/verletIntegrator.cpp
    src/BruteForceSimulator.cpp
)

# Optional GIF support
option(ENABLE_GIF_EXPORT "Enable saving simulation as GIF" ON)

# Find SFML
find_package(SFML REQUIRED COMPONENTS System Window)

# Find SDL2
find_package(SDL2 REQUIRED)

# Find SDL2_gfx
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_GFX REQUIRED SDL2_gfx)

# Create executable
add_executable(simulation ${SOURCES})

# Include directories
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_GFX_INCLUDE_DIRS})

# Link directories
link_directories(${SDL2_LIBRARY_DIRS} ${SDL2_GFX_LIBRARY_DIRS})

# Link libraries
target_link_libraries(simulation
    SFML::System
    SFML::Window
    ${SDL2_LIBRARIES}
    ${SDL2_GFX_LIBRARIES}
)

# Conditionally link giflib
if(ENABLE_GIF_EXPORT)
    message(STATUS "GIF export enabled.")
    target_link_libraries(simulation gif)
    target_compile_definitions(simulation PRIVATE ENABLE_GIF_EXPORT)
else()
    message(STATUS "GIF export disabled.")
endif()

