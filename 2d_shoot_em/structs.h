#ifndef ATC_STRUCTS_H
#define ATC_STRUCTS_H

#include "SDL2/SDL.h"

typedef struct {
  SDL_Renderer* renderer;
  SDL_Window* window;
} App;

/**
 * @brief Object for holding color values 
 * 
 */
typedef struct {
  int r;
  int g;
  int b;
  int a;
} Color;

#endif