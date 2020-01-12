#include "input.h"


void do_key_down(
  App* app,
  SDL_KeyboardEvent* event) {

  if (event->repeat == 0) {
		if (event->keysym.scancode == SDL_SCANCODE_UP) {
			app->up = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
			app->down = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
			app->left = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
			app->right = 1;
		}
	}
}

void do_key_up(
  App* app,
  SDL_KeyboardEvent* event) {
  
  if (event->repeat == 0) {
		if (event->keysym.scancode == SDL_SCANCODE_UP) {
			app->up = 0;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
			app->down = 0;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
			app->left = 0;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
			app->right = 0;
		}
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
      do_key_down(app, &event.key);
      break;
    /* If any key is released */
    case SDL_KEYUP:
      do_key_up(app, &event.key);
      break;
    default:
      break;  
    }
  }
  return 1;
}