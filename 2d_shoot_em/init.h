#ifndef ATC_INIT_H
#define ATC_INIT_H

#include "defs.h"
#include "structs.h"

/**
 * @brief Initialize the sdl window
 * 
 * @return int -1 if there was an error. 1 if successful
 */
int init_sdl(App* app);

/**
 * @brief Cleanup any applications
 * 
 */
void cleanup(App* app);

#endif