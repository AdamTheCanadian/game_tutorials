cmake_minimum_required(VERSION 3.10)
project(shoot_em VERSION 0.0.1)

find_package(SDL2 REQUIRED)
include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})