#include "stage.h"
#include "util.h"

static Entity *player;
static SDL_Texture* bullet_texture;
static SDL_Texture* enemy_texture;
static SDL_Texture* alien_bullet_texture;
static SDL_Texture* player_texture;
static int enemy_spawn_timer;
static int stage_reset_timer;

void init_stage() {

  app.delgate.logic = logic;
  app.delgate.draw = draw;

  memset(&stage, 0, sizeof(Stage));
  stage.fighter_tail = &stage.fighter_head;
  stage.bullet_tail = &stage.bullet_head;

  /* Load the bullet now so dont need to reload every time a bullet is fired */
  bullet_texture = load_texture("images/playerBullet.png");
  enemy_texture = load_texture("images/enemy.png");
	alien_bullet_texture = load_texture("images/alienBullet.png");
  player_texture = load_texture("images/player.png");
	enemy_spawn_timer = 0;
	reset_stage();
}

void init_player() {

  player = malloc(sizeof(Entity));
  memset(player, 0, sizeof(Entity));
  stage.fighter_tail->next = player;
  stage.fighter_tail = player;

	player->health = 1;
  player->x = 100;
  player->y = 100;
	player->side = SIDE_PLAYER;
	player->texture = player_texture;
  SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void logic() {
  do_player();
	do_enemies();
  do_fighters();
  do_bullets();
  spawn_enemies();
	clip_player();
	if (player == NULL && --stage_reset_timer <= 0) {

		reset_stage();
	}
}

void do_player() {
  
	if (player != NULL ) {
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
	
	}
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
		if (bullet_hit_fighter(b) || b->x < -b->w || b->y < -b->h || b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT) {
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
	bullet->side = SIDE_PLAYER;
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
	
	prev = &stage.fighter_head;
	
	for (e = stage.fighter_head.next ; e != NULL ; e = e->next) {
		e->x += e->dx;
		e->y += e->dy;
		
		if (e != player && e->x < -e->w) {
			e->health = 0;
		}
		
		if (e->health == 0) {
			if (e == player) {
				player = NULL;
			}
			
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
		enemy->side = SIDE_ALIEN;
		enemy->texture = enemy_texture;
		enemy->health = 1;
		enemy->reload = FPS * (1 + (rand() % 3));
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

int bullet_hit_fighter(Entity* b) {
	
	Entity *e;
	
	for (e = stage.fighter_head.next ; e != NULL ; e = e->next) {
		if (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h)) {
			b->health = 0;
			e->health = 0;
			
			return 1;
		}
	}
}

void reset_stage() {

	Entity *e;
	
	while (stage.fighter_head.next) {
		e = stage.fighter_head.next;
		stage.fighter_head.next = e->next;
		free(e);
	}
	
	while (stage.bullet_head.next) {
		e = stage.bullet_head.next;
		stage.bullet_head.next = e->next;
		free(e);
	}
	
	memset(&stage, 0, sizeof(Stage));
	stage.fighter_tail = &stage.fighter_head;
	stage.bullet_tail = &stage.bullet_head;
	
	init_player();
	
	enemy_spawn_timer = 0;
	
	stage_reset_timer = FPS * 2;
}

void clip_player() {
	if (player != NULL) {
		if (player->x < 0) {
			player->x = 0;
		}
		
		if (player->y < 0) {
			player->y = 0;
		}
		
		if (player->x > SCREEN_WIDTH / 2) {
			player->x = SCREEN_WIDTH / 2;
		}
		
		if (player->y > SCREEN_HEIGHT - player->h) {
			player->y = SCREEN_HEIGHT - player->h;
		}
	}
}

void fire_alien_bullet(Entity* e) {

	Entity *bullet;
	
	bullet = malloc(sizeof(Entity));
	memset(bullet, 0, sizeof(Entity));
	stage.bullet_tail->next = bullet;
	stage.bullet_tail = bullet;
	
	bullet->x = e->x;
	bullet->y = e->y;
	bullet->health = 1;
	bullet->texture = alien_bullet_texture;
	bullet->side = e->side;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
	
	bullet->x += (e->w / 2) - (bullet->w / 2);
	bullet->y += (e->h / 2) - (bullet->h / 2);
	
	calc_slope(player->x + (player->w / 2), player->y + (player->h / 2), e->x, e->y, &bullet->dx, &bullet->dy);
	
	bullet->dx *= ALIEN_BULLET_SPEED;
	bullet->dy *= ALIEN_BULLET_SPEED;
	
	bullet->side = SIDE_ALIEN;
	
	e->reload = (rand() % FPS * 2);

}

void do_enemies() {
	
	Entity *e;
	
	for (e = stage.fighter_head.next ; e != NULL ; e = e->next) {
		if (e != player && player != NULL && --e->reload <= 0) {
			fire_alien_bullet(e);
		}
	}
}