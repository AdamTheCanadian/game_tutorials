#include "init.h"

#include "sdl.h"

int init_sdl(
  App* app,
  const char* windowName) {

  int render_flags = SDL_RENDERER_ACCELERATED; 
  int window_flags = 0;
  app->window = SDL_CreateWindow(
    windowName,
    /* UNDEFINED means place the window wherever */
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, 
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    window_flags);
  
  if (!app->window) {
    printf("Failed to open window: %s\n", SDL_GetError());
    return -1;
  }
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  app->renderer = SDL_CreateRenderer(
    app->window, 
    /* SDL to use the first graphics acceleration device it finds */
    -1, 
    render_flags);
  if (!app->renderer) {
    printf("Failed to open window: %s\n", SDL_GetError());
    return -1;
  }
  /* Initialize sdl image library that will allow us to load png and jpg 
    images */
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
  return 1;
}

void cleanup(App* app)
{
	SDL_DestroyRenderer(app->renderer);
	
	SDL_DestroyWindow(app->window);
	
	SDL_Quit();
}
