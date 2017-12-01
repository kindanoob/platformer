#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

const std::string fonts_path = "resources/fonts/";
const std::string textures_path = "resources/textures/";


const int SCREEN_WIDTH = 800;//screen width in pixels
const int SCREEN_HEIGHT = 600;//screen height in pixels
const int HERO_TILE_WIDTH = 24;
const int HERO_TILE_HEIGHT = 32;

const int GROUND = SCREEN_HEIGHT;//cutoff value of x coordinate for gravity force, 
                                 //for all values greater than cutoff there is no gravity

#endif // CONFIG_H_
