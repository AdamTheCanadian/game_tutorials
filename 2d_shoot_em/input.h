#ifndef ATC_INPUT_H
#define ATC_INPUT_H

#include "structs.h"
#include "sdl.h"

void do_key_down(
  App* app,
  SDL_KeyboardEvent* event);

void do_key_up(
  App* app,
  SDL_KeyboardEvent* event);

/**
 * @brief Process any inputs (keyboard, mouse) from the sdl
 * 
 * @return int -1 if there was request to exit
 */
int do_input(
  App* app);

#endif