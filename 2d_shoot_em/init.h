#ifndef ATC_INIT_H
#define ATC_INIT_H

#include "defs.h"
#include "structs.h"

/**
 * @brief Initialize the sdl window
 * 
 */
void init_sdl(App* app);

/**
 * @brief Cleanup any applications
 * 
 */
void cleanup(App* app);

#endif