#include "stage.h"


static Entity *player;
static SDL_Texture *bullet_texture;

void init_stage() {

  app.delgate.logic = logic;
  app.delgate.draw = draw;

  memset(&stage, 0, sizeof(Stage));
  stage.fighter_tail = &stage.fighter_head;
  stage.bullet_tail = &stage.bullet_head;

  init_player();
  /* Load the bullet now so dont need to reload every time a bullet is fired */
  bullet_texture = load_texture("images/playerBullet.png");
}

void init_player() {
  player = malloc(sizeof(Entity));
  memset(player, 0, sizeof(Entity));
  stage.fighter_tail->next = player;
  stage.fighter_tail = player;

  player->x = 100;
  player->y = 100;
  player->texture = load_texture("images/player.png");
  SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void logic() {
  do_player();
  do_bullets();
}

void do_player() {
  player->dx = player->dy = 0;
	
	if (player->reload > 0) {
		player->reload--;
	}
	
	if (app.keyboard[SDL_SCANCODE_UP]) {
		player->dy = -PLAYER_SPEED;
	}
	
	if (app.keyboard[SDL_SCANCODE_DOWN]) {
		player->dy = PLAYER_SPEED;
	}
	
	if (app.keyboard[SDL_SCANCODE_LEFT]) {
		player->dx = -PLAYER_SPEED;
	}
	
	if (app.keyboard[SDL_SCANCODE_RIGHT]) {
		player->dx = PLAYER_SPEED;
	}
	
	if (app.keyboard[SDL_SCANCODE_LCTRL] && player->reload == 0) {
		fire_bullet();
	}
	
	player->x += player->dx;
	player->y += player->dy;
}

void do_bullets() {

  Entity *b, *prev;
	
	prev = &stage.bullet_head;
	
  /* Loop through the linked list and update all bullets */
	for (b = stage.bullet_head.next ; b != NULL ; b = b->next) {
    /* Update bullet location */
		b->x += b->dx;
		b->y += b->dy;
		/* If bullet has passed out of screen delete it */
		if (b->x > SCREEN_WIDTH) {
			if (b == stage.bullet_tail) {
				stage.bullet_tail = prev;
			}
			
			prev->next = b->next;
			free(b);
			b = prev;
		}
		
		prev = b;
	}
}

void fire_bullet() {

  Entity* bullet;

  bullet = malloc(sizeof(Entity));
  memset(bullet, 0, sizeof(Entity));
  /* Add the new bullet to the list */
  stage.bullet_tail->next = bullet;
  stage.bullet_tail = bullet;

  /* Bullets originate at the current players location */
  bullet->x = player->x;
  bullet->y = player->y;

  bullet->dx = PLAYER_BULLET_SPEED;
  bullet->health = 1;
  bullet->texture = bullet_texture;
  SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

  /* Position the bullet at the center(ish) of the player instead of top */
  bullet->y += (player->h / 2) - (bullet->h / 2);
  /* This says 8 frames must pass before player can fire again */
  player->reload = 8;
}

void draw() {
  draw_player();
  draw_bullets();
}

void draw_player() {
  blit(player->texture, player->x, player->y);
}

void draw_bullets() {
  Entity* b;
  for (b = stage.bullet_head.next; b != NULL; b = b->next) {
    blit(b->texture, b->x, b->y);
  }
}