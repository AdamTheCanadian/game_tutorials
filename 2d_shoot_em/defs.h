#ifndef ATC_DEFS_H
#define ATC_DEFS_H

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/* The width of the game window in pixels */
#define SCREEN_WIDTH 1280
/* The height of the game window in pixels */
#define SCREEN_HEIGHT 720

/* Number of potential keyboard inputs */
#define MAX_KEYBOARD_KEYS 350

#define PLAYER_SPEED 4
#define PLAYER_BULLET_SPEED 16

#define SIDE_PLAYER 0
#define SIDE_ALIEN  1

#endif