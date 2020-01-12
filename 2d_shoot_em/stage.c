#include "stage.h"


static Entity *player;
static SDL_Texture *bullet_texture;
static SDL_Texture *enemy_texture;
static int enemy_spawn_timer;

void init_stage() {

  app.delgate.logic = logic;
  app.delgate.draw = draw;

  memset(&stage, 0, sizeof(Stage));
  stage.fighter_tail = &stage.fighter_head;
  stage.bullet_tail = &stage.bullet_head;

  init_player();
  /* Load the bullet now so dont need to reload every time a bullet is fired */
  bullet_texture = load_texture("images/playerBullet.png");
  enemy_texture = load_texture("images/enemy.png");
  enemy_spawn_timer = 0;
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
  do_fighters();
  do_bullets();
  spawn_enemies();
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
  draw_fighters();
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

void do_fighters() {
  
  Entity *e, *prev;
	
	for (e = stage.fighter_head.next ; e != NULL ; e = e->next) {
		e->x += e->dx;
		e->y += e->dy;
		
		if (e != player && e->x < -e->w) {
			if (e == stage.fighter_tail) {
				stage.fighter_tail = prev;
			}
			
			prev->next = e->next;
			free(e);
			e = prev;
		}
		
		prev = e;
	}
}

void spawn_enemies() {
  Entity *enemy;
	
	if (--enemy_spawn_timer <= 0) {
    
		enemy = malloc(sizeof(Entity));
		memset(enemy, 0, sizeof(Entity));
		stage.fighter_tail->next = enemy;
		stage.fighter_tail = enemy;
		
		enemy->x = SCREEN_WIDTH;
		enemy->y = rand() % SCREEN_HEIGHT;
		enemy->texture = enemy_texture;
		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);
		
		enemy->dx = -(2 + (rand() % 4));
		
		enemy_spawn_timer = 30 + (rand() % 60);
	}
}

void draw_fighters() {
  
  Entity *e;
	
	for (e = stage.fighter_head.next ; e != NULL ; e = e->next) {
		blit(e->texture, e->x, e->y);
	}
}