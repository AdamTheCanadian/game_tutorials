#ifndef ATC_DRAW_H
#define ATC_DRAW_H

#include "structs.h"
#include "sdl.h"

/**
 * @brief Prepare the scene before presenting to the screen
 * 
 * @param app 
 */
void prepare_scene(App* app);

/**
 * @brief 
 * 
 * @param app 
 */
void present_scene(App* app);

/**
 * @brief Load a file and convert it to a sdl texture
 * 
 * @param filename 
 * @return SDL_Texture* 
 */
SDL_Texture* load_texture(
  App* app,
  char* filename);

/**
 * @brief Draw a texture at a certain location
 * 
 * @param app 
 * @param texture 
 * @param x 
 * @param y 
 */
void blit(
  App* app,
  SDL_Texture* texture,
  int x,
  int y);

#endif