# Game Tutorial Implementation

Following along the game tutorials outlined at https://www.parallelrealities.co.uk/tutorials/

## Dependencies

Games are built around libsdl. I am running ubuntu 18, so to install:

`sudo apt install libsdl2-dev`

SDL image is not part of standard lib sdl so needto also install that.
`sudo apt-get install libsdl2-image-dev`

CMake is used as the build system, vs make in the original authors. 

## Notes to reader

I changed a few things in the original implementation. This was done for a few reasons:
1. Easier experimentation. For example I wanted to try running multiple apps in the same program. In the original implementation `App` is a global variable and accessed in the functions. In my implementation its passed to functions by pointer.
2. Naming convention. I have my own weird code style and wanted to follow that.
3. Added error codes to void functions instead of having the function call exit()
4. Used CMake and CMakeLists as the build system since this is what I am more familiar with.
