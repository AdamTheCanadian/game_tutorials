#include <stdio.h>
#include "defs.h"
#include "structs.h"
#include "input.h"
#include "draw.h"
#include "init.h"

int main() {
 
  App app;
  Entity player;

  memset(&app, 0, sizeof(App));
  memset(&player, 0, sizeof(Entity));

  if (init_sdl(&app, "Shooter 01") < 0) {
    goto exit_error;
  }
  
  player.x = 100;
  player.y = 100;
  player.texture = load_texture(
    &app,
    "images/player.png");

  while(1) {
    prepare_scene(&app);

    if (do_input() < 0) {
      goto exit_program;
    }

    blit(&app, player.texture, player.x, player.y);

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