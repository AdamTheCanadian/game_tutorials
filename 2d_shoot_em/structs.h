#ifndef ATC_STRUCTS_H
#define ATC_STRUCTS_H

#include "sdl.h"
#include "defs.h"

/* Need to forward declare the Entity object for the linked list in Entity */
typedef struct Entity Entity; 
typedef struct {

  /* Function pointers for handling logic (keyboard for ex) */
  void (*logic)(void);
  /* Function pointer for handling drawing */
  void (*draw)(void);
} Delegate;

typedef struct {
  SDL_Renderer* renderer;
  SDL_Window* window;
  Delegate delgate;
  int keyboard[MAX_KEYBOARD_KEYS];

} App;

/**
 * @brief Struct for holding a texture and the location of the texture
 * 
 */
struct Entity {
	float x;
	float y;
  int w;
  int h;
  float dx;
  float dy;
  /* Health of 0 means the entity can be deleted */
  int health;
  /* Flag indicating ability to fire*/
  int reload;
  int side;
	SDL_Texture *texture;
  /* Linked list, pointer to next entity */
  Entity* next;
};

/**
 * @brief For holding information on all bullets and fighters
 * 
 */
typedef struct {
  Entity fighter_head, *fighter_tail;
  Entity bullet_head, *bullet_tail; 
} Stage;

#endif