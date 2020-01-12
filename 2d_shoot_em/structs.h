#ifndef ATC_STRUCTS_H
#define ATC_STRUCTS_H

#include "sdl.h"

typedef struct {
  SDL_Renderer* renderer;
  SDL_Window* window;
  /* Variables for tracking movement from keyboard input */
  int up;
  int down;
  int left;
  int right;
  /* For storing shoot input from keyboard */
  int fire;
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
  int dx;
  int dy;
  /* Health of 0 means the entity can be deleted */
  int health;
	SDL_Texture *texture;
} Entity;

#endif