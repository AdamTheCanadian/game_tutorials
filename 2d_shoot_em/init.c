#include "init.h"

#include "SDL2/SDL.h"

void init_sdl(App* app) {

  int render_flags = SDL_RENDERER_ACCELERATED; 
  int window_flags = 0;
  app->window = SDL_CreateWindow(
    "Shooter 01",
    /* UNDEFINED means place the window wherever */
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, 
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    window_flags);
  
  if (!app->window) {
    printf("Failed to open window: %s\n", SDL_GetError());
    exit(1);
  }
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  app->renderer = SDL_CreateRenderer(
    app->window, 
    /* SDL to use the first graphics acceleration device it finds */
    -1, 
    render_flags);
  if (!app->renderer) {
    printf("Failed to open window: %s\n", SDL_GetError());
    exit(1);
  }
}

void cleanup(App* app)
{
	SDL_DestroyRenderer(app->renderer);
	
	SDL_DestroyWindow(app->window);
	
	SDL_Quit();
}
