#ifndef MAP_OBSTACLE_H_
#define MAP_OBSTACLE_H_

#include "entity.h"


class Map_obstacle: public Entity {
public:
    Map_obstacle(const sf::Texture& m_texture, const std::string& m_name, 
    	double m_x, double m_y, double m_w, double m_h, int row, int col):
        Entity(m_texture, m_name, m_x, m_y, m_w, m_h, row, col) {
        set_animations();
        animation_manager.set_animation("fire_animation");
    }
    void set_animations();
    void update(double time, GameMap &game_map, double offset_x, double offset_y);
};

void Map_obstacle::set_animations() {
    animation_manager.create("fire_animation", texture, 0, 0, w, h, 2, 0.001, w, 1);
};

void Map_obstacle::update(double time, GameMap &game_map, double offset_x, double offset_y) {
    animation_manager.tick(time);
}

#endif // MAP_OBSTACLE_H_
