#ifndef ATC_STRUCTS_H
#define ATC_STRUCTS_H

#include "sdl.h"

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

/**
 * @brief Struct for holding a texture and the location of the texture
 * 
 */
typedef struct {
	int x;
	int y;
	SDL_Texture *texture;
} Entity;

#endif