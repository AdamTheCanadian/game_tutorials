#include "input.h"
#include "SDL2/SDL.h"

void do_input() {
  
  SDL_Event event;
  /* Keep looping until no events are left */
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
    case SDL_QUIT:
      exit(0);
      break;
    default:
      break;  
    }
  }
}