#ifndef ENEMY_H_
#define ENEMY_H_

#include "entity.h"

const int ENEMY_FALLING_COEFF = 10;

class Enemy: public Entity {
public:
    //enum ENEMY_TYPE{BASIC, MIDDLE, ADVANCED};
    //ENEMY_TYPE enemy_type;
    bool on_ground;
    //int damage;
    //double dead_duration;//time in milliseconds for which enemy is being dead
    Enemy(const sf::Texture &m_texture, const std::string &m_name, double m_x, double m_y, double m_w, double m_h, int row, int col):
        Entity(m_texture, m_name, m_x, m_y, m_w, m_h, row, col) {
            //state = STAY;
            health = 30;
            on_ground = true;
            //enemy_type = BASIC;
            dx = 0.05;
            dead_duration = 0;
            damage = 30;
            set_animations();
            animation_manager.set_animation("enemy_walk_right");//since initially dx is positive
    }
    void check_map_collisions(GameMap &game_map, DIRECTION dir);
    void update(double time, GameMap &game_map, double offset_x, double offset_y);
    void set_animations();
};

void Enemy::check_map_collisions(GameMap &game_map, DIRECTION dir) {
    if (!is_alive) {
        return;
    }
    for (int i = get_y() / h ; i < (get_y() + h) / h; ++i) {
        for (int j = get_x() / w; j < (get_x() + w) / w; ++j) {
            if (game_map.char_map[i][j] == 'B') {
                if ((dx > 0) && (dir == HORIZONTAL)) {
                    set_x(j * w - w);
                }
                if ((dx < 0) && (dir == HORIZONTAL)) {
                    set_x(j * w + w);
                }
                dx *= -1;
                if ((dy > 0) && (dir == VERTICAL)) {
                    set_y(i * h - h);
                    dy = 0.0;
                    on_ground = true;
                }
                if ((dy < 0) && (dir == VERTICAL)) {
                    set_y(i * h + h);
                    dy = 0.0;
                }
            }
        }
    }
}

void Enemy::update(double time, GameMap &game_map, double offset_x, double offset_y) {
        if (!is_alive) {
            dead_duration += time / TIME_ADJUSTMENT;
            set_y(get_y() + time / ENEMY_FALLING_COEFF);
            sprite.setPosition(get_x() - offset_x, get_y() - offset_y);
            return;
        }
        set_x(get_x() + dx * time);
        check_map_collisions(game_map, HORIZONTAL);
        if (dx > 0) {
            animation_manager.set_animation("enemy_walk_right");
        } else {
            animation_manager.set_animation("enemy_walk_left");
        }
        animation_manager.tick(time);
}

void Enemy::set_animations() {
    animation_manager.create("enemy_walk_left", texture, 0 * w, h, w, h, 3, 0.005, w);
    animation_manager.create("enemy_walk_right", texture, 0 * w, 2 * h, w, h, 3, 0.005, w);
}

#endif //ENEMY_H_
