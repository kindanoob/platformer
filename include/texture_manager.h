#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <SFML/Graphics.hpp>
#include <map>
#include "resource_manager.h"

enum class Texture_name {
    player_texture, basic_enemy_texture, fire_texture, moving_platform_texture, bullet_texture
};

class Texture_manager: public Resource_manager<Texture_name, sf::Texture> {
public:
    Texture_manager();
};

#endif // TEXTURE_MANAGER_H_
