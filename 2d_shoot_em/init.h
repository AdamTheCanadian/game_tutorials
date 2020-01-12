#ifndef ATC_INIT_H
#define ATC_INIT_H

#include "defs.h"
#include "structs.h"

extern App app;

/**
 * @brief Initialize the sdl window
 * 
 * @param windowName name of the window for the application
 * 
 * @return int -1 if there was an error. 1 if successful
 */
int init_sdl(
  const char* windowName);

/**
 * @brief Cleanup any applications
 * 
 */
void cleanup(App* app);

#endif