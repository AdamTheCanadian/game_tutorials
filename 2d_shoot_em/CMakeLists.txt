cmake_minimum_required(VERSION 3.10)
project(shoot_em VERSION 0.0.1)

# For SDL2_image
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

include_directories()

set(LIBRARY_NAME ${PROJECT_NAME}_lib)

set(SOURCE_FILES
  sdl.h
  defs.h
  structs.h
  init.h
  init.c
  input.h
  input.c
  draw.h
  draw.c)

add_library(${LIBRARY_NAME} ${SOURCE_FILES})
# Need to force the linker language to csince library is only header files
set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(${LIBRARY_NAME} 
  ${SDL2_LIBRARIES} 
  ${SDL2_IMAGE_LIBRARIES})

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} ${LIBRARY_NAME})