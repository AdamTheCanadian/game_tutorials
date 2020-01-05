#include "input.h"
#include "sdl.h"

int do_input() {
  
  SDL_Event event;
  /* Keep looping until no events are left */
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
    case SDL_QUIT:
      return -1;
      break;
    default:
      break;  
    }
  }
  return 1;
}