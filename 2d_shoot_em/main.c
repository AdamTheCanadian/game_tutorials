#include <stdio.h>
#include "defs.h"
#include "structs.h"
#include "input.h"
#include "draw.h"
#include "init.h"

int main() {
  printf("Hello from game_tutorials\n");
  /* Test to make sure SDL is being linked correctly */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

  App app;
  memset(&app, 0, sizeof(App));
  init_sdl(&app);
  
  while(1) {
    prepare_scene(&app);

    do_input();

    present_scene(&app);

    SDL_Delay(16);
  }
  return 0;
}