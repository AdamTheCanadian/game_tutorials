#include <stdio.h>
#include "SDL2/SDL.h"

int main() {
  printf("Hello from game_tutorials\n");
  /* Test to make sure SDL is being linked correctly */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
  printf("SDL linked correctly\n");
}