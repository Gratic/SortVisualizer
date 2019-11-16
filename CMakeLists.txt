cmake_minimum_required(VERSION 3.1)

project(SortVisualizer)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/Libraries/SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS window system graphicsREQUIRED)
add_executable(SortVisualizer main.cpp Sources/Value.cpp Headers/Value.h Sources/Sort.cpp Headers/Sort.h)
target_link_libraries(SortVisualizer sfml-window sfml-system sfml-graphics)