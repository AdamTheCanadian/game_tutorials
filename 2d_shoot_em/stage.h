#ifndef ATC_STAGE_H
#define ATC_STAGE_H

#include "structs.h"
#include "draw.h"

extern void blit(SDL_Texture *texture, int x, int y);
extern SDL_Texture *load_texture(char *filename);

extern App app;
extern Stage stage;

/**
 * @brief
 * 
 * @param app 
 */
void init_stage();

void init_player();

void logic();

void do_player();

void do_bullets();

void fire_bullet();

void draw();

void draw_player();

void draw_bullets();

void draw_fighters(); 

void do_fighters();

void spawn_enemies();

int bullet_hit_fighter(Entity* b);

#endif