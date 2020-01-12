#include "input.h"


void do_key_down(
  SDL_KeyboardEvent* event) {

  if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
    app.keyboard[event->keysym.scancode] = 1;
  }
}

void do_key_up(
  SDL_KeyboardEvent* event) {
  
  if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
    app.keyboard[event->keysym.scancode] = 0;
  }
}

int do_input(App* app) {
  
  SDL_Event event;
  /* Keep looping until no events are left */
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
    case SDL_QUIT:
      return -1;
      break;
    /* If any key is pressed down */
    case SDL_KEYDOWN:
      do_key_down(&event.key);
      break;
    /* If any key is released */
    case SDL_KEYUP:
      do_key_up(&event.key);
      break;
    default:
      break;  
    }
  }
  return 1;
}