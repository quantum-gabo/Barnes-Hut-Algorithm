# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Simulation)

# Specify the C++ standard to use
set(CMAKE_CXX_STANDARD 20)

# Add the include directory
include_directories(include)

# Add the source files
set(SOURCES
    src/main.cpp
    src/Body.cpp
    src/verletIntegrator.cpp
    src/vector2D.cpp
    src/BruteForceSimulator.cpp
)

# Find SFML package
find_package(SFML REQUIRED COMPONENTS System Window)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Find SDL2_gfx package
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_GFX REQUIRED SDL2_gfx)

# Create the executable
add_executable(simulation ${SOURCES})

# Include directories for SDL2 and SDL2_gfx
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_GFX_INCLUDE_DIRS})

# Link directories for SDL2 and SDL2_gfx
link_directories(${SDL2_LIBRARY_DIRS} ${SDL2_GFX_LIBRARY_DIRS})

# Link SFML, SDL2, and SDL2_gfx libraries to your project
target_link_libraries(simulation SFML::System SFML::Window ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES})
