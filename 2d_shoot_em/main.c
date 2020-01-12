#include <stdio.h>
#include "defs.h"
#include "structs.h"
#include "input.h"
#include "draw.h"
#include "init.h"
#include "stage.h"

static void cap_frame_rate(long* then, float* remainder);

int main() {
 
  long then;
  float remainder;

  memset(&app, 0, sizeof(App));

  if (init_sdl("Shooter 01") < 0) {
    goto exit_error;
  }
  
  init_stage();

  then = SDL_GetTicks();
  remainder = 0;

  while(1) {
    prepare_scene(&app);

    if (do_input(&app) < 0) {
      goto exit_program;
    }
    
    app.delgate.logic();
    app.delgate.draw();
    present_scene();
    cap_frame_rate(&then, &remainder);
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

static void cap_frame_rate(long* then, float* remainder) {

  long wait, frame_time;
  wait = 16 + *remainder;

  *remainder -= (int)*remainder;
  frame_time = SDL_GetTicks() - *then;

  wait -= frame_time;
  if (wait < 1) {
    wait = 1;
  }
  SDL_Delay(wait);
  *remainder += 0.667;
  *then = SDL_GetTicks();
}