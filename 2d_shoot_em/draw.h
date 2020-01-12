#ifndef ATC_DRAW_H
#define ATC_DRAW_H

#include "structs.h"
#include "sdl.h"
#include "main.h"

extern App app;

/**
 * @brief Prepare the scene before presenting to the screen
 * 
 */
void prepare_scene();

/**
 * @brief 
 * 
 */
void present_scene();

/**
 * @brief Load a file and convert it to a sdl texture
 * 
 * @param filename 
 * @return SDL_Texture* 
 */
SDL_Texture* load_texture(
  char* filename);

/**
 * @brief Draw a texture at a certain location
 * 
 * @param texture 
 * @param x 
 * @param y 
 */
void blit(
  SDL_Texture* texture,
  int x,
  int y);

#endif