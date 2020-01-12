#include <stdio.h>
#include "defs.h"
#include "structs.h"
#include "input.h"
#include "draw.h"
#include "init.h"

int main() {
 
  App app;
  Entity player;
  Entity bullet;

  memset(&app, 0, sizeof(App));
  memset(&player, 0, sizeof(Entity));
  memset(&bullet, 0, sizeof(Entity));

  if (init_sdl(&app, "Shooter 01") < 0) {
    goto exit_error;
  }
  
  player.x = 100;
  player.y = 100;
  player.texture = load_texture(
    &app,
    "images/player.png");

  bullet.texture = load_texture(
    &app,
    "images/playerBullet.png");

  while(1) {
    prepare_scene(&app);

    if (do_input(&app) < 0) {
      goto exit_program;
    }

    player.x += player.dx;
    player.y += player.dy;

    if (app.up) {
      player.y -= 4;
    }
    if (app.down) {
      player.y += 4;
    }
    if (app.left) {
      player.x -= 4;
    }
    if (app.right) {
      player.x += 4;
    }

    if (app.fire && bullet.health == 0) {
      /* Bullet originates at the player location */
      bullet.x = player.x;
      bullet.y = player.y;
      bullet.dx = 16;
      bullet.dy = 0;
      bullet.health = 1;
    }
    /* Move the bullet in the screen */
    bullet.x += bullet.dx;
		bullet.y += bullet.dy;
    /* Bullet has gone out of screen so does not need to be rendered */
    if (bullet.x > SCREEN_WIDTH) {
			bullet.health = 0;
		}
    blit(&app, player.texture, player.x, player.y);
    /* Render the bullet if active */
    if (bullet.health > 0) {
			blit(&app, bullet.texture, bullet.x, bullet.y);
		}
    present_scene(&app);

    SDL_Delay(16);
  }
  return EXIT_SUCCESS;

exit_error:
  cleanup(&app);
  return EXIT_FAILURE;

exit_program:
  printf("Exiting program thanks for playing\n");
  cleanup(&app);
  return EXIT_SUCCESS;

}