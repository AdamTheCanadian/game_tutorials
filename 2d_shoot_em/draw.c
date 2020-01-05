#include "draw.h"
#include "sdl.h"

void prepare_scene(App* app) {

  SDL_SetRenderDrawColor(
    app->renderer, 
    96,
    128,
    255,
    255);
  
  SDL_RenderClear(app->renderer);
}

void present_scene(App* app) {
  SDL_RenderPresent(app->renderer);
}