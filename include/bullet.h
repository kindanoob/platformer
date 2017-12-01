#ifndef BULLET_H_
#define BULLET_H_

#include "entity.h"

const double BULLET_SPEED = 0.6;
const int BULLET_SIZE = 4;//in pixels

class Bullet: public Entity {
public:
    int direction;
    double speed;
    Bullet(const sf::Texture &m_texture, const std::string &m_name, 
        double m_x, double m_y, double m_w, double m_h, int row, int col,
           int m_direction) :
        Entity(m_texture, m_name, m_x, m_y, m_w, m_h, row, col) {
        set_direction(m_direction);
        speed = BULLET_SPEED;
        set_is_alive(true);
        set_damage(10);
        set_dy(0);
        set_animations();
        animation_manager.set_animation("bullet_fly");
    }
    void update(double time, GameMap &game_map, double offset_x, double offset_y);
    void check_map_collisions(GameMap &game_map);
    void set_animations();
    void set_direction(int l_direction);
    int get_direction();
};


void Bullet::check_map_collisions(GameMap &game_map) {
    if (!get_is_alive()) {
        return;
    }
    int tile_side_length = game_map.tile_side_length;
    for (int i = get_y() / tile_side_length; i < (get_y() + get_h()) / tile_side_length; ++i) {
        for (int j = get_x() / tile_side_length; j < (get_x() + get_w()) / tile_side_length; ++j) {
            if (game_map.char_map[i][j] == 'B') {
                set_is_alive(false);
                return;
            }
        }
    }
}


void Bullet::update(double time, GameMap &game_map, double offset_x, double offset_y) {
    switch(get_direction()) {
        case 0 : {//shoot left
            dx = -speed;
            dy = 0;
            break;
        }
        case 1 : {//shoot right
            dx = speed;
            dy = 0;
            break;
        }
        case 2 : {//shoot up
            dx = 0;
            dy = speed;
            break;
        }
        case 3 : {//shoot TODO
            dx = -speed;
            dy = 0;
            break;
        }
        case 4 : {//shoot TODO
            dx = speed;
            dy = 0;
            break;
        }
        case 5 : {//shoot TODO
            dx = 0;
            dy = speed;
            break;
        }
    }
    set_x(get_x() + get_dx() * time);
    set_y(get_y() + get_dy() * time);
    if (get_x() <= 0) {//check for bullet moving out of screen due to CPU overload
        set_x(1);
    }
    if (get_y() <= 0) {
        set_y(1);
    }
    check_map_collisions(game_map);
}

void Bullet::set_animations() {
    animation_manager.create("bullet_fly", texture, 0 * w, 0 * h, w, h, 1, 0.05, w);
}

void Bullet::set_direction(int l_direction) {
    direction = l_direction;
}

int Bullet::get_direction() {
    return direction;
}

#endif // BULLET_H_
