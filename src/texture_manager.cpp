

#include "config.h"
#include "texture_manager.h"


Texture_manager::Texture_manager() {
    add_resource(Texture_name::player_texture, textures_path + "full_tileset_24_by_32.png");
    add_resource(Texture_name::basic_enemy_texture, textures_path + "mypic4.png");
    add_resource(Texture_name::fire_texture, textures_path + "fire_high_4.png");
    add_resource(Texture_name::moving_platform_texture, textures_path + "moving_platform.png");
    add_resource(Texture_name::bullet_texture, textures_path + "bullet_4_by_4.png");
}
