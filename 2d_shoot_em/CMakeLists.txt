cmake_minimum_required(VERSION 3.10)
project(shoot_em VERSION 0.0.1)

find_package(SDL2 REQUIRED)
include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})

set(LIBRARY_NAME ${PROJECT_NAME}_lib)

set(SOURCE_FILES
  defs.h)

add_library(${LIBRARY_NAME} ${SOURCE_FILES})
# Need to force the linker language to csince library is only header files
set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(${LIBRARY_NAME} ${SDL2_LIBRARIES})

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} ${LIBRARY_NAME})