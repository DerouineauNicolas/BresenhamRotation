cmake_minimum_required (VERSION 2.8.11)
project (BresenhamRotation)

#add_compile_options(-Wall -Wextra -pedantic)

add_executable (BresenhamRotation src/main.cpp src/rotation.cpp)
target_include_directories(BresenhamRotation PUBLIC src src/import)