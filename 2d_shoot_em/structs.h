#ifndef ATC_STRUCTS_H
#define ATC_STRUCTS_H

#include "SDL2/SDL.h"

typedef struct {
  SDL_Renderer* renderer;
  SDL_Window* window;
} App;

#endif