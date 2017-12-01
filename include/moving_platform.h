#ifndef MOVINGPLATFORM_H_
#define MOVINGPLATFORM_H_

#include "entity.h"

const int ONE_WAY_DURATION = 3000;//in milliseconds
const double MOVING_PLATFORM_SPEED_X = 0.1;



class MovingPlatform: public Entity {
public:
    MovingPlatform(const sf::Texture &m_texture, const std::string &m_name, double m_x, double m_y, double m_w, double m_h, int row, int col):
        Entity(m_texture, m_name, m_x, m_y, m_w, m_h, row, col) {
        set_dx(MOVING_PLATFORM_SPEED_X);
        set_dy(0);
        set_animations();
    }
	void update(double time, GameMap &game_map, double offset_x, double offset_y);
	void check_map_collisions(GameMap &game_map, DIRECTION dir);
	void set_animations();
};


void MovingPlatform::update(double time, GameMap &game_map, double offset_x, double offset_y) {
    set_x(get_x() + get_dx() * time);
    check_map_collisions(game_map, HORIZONTAL);
    timer += time;
    if (timer > ONE_WAY_DURATION) {
        set_dx(-get_dx());
        set_timer(0);
    }
    check_map_collisions(game_map, VERTICAL);
    sprite.setPosition(get_x() - offset_x, get_y() - offset_y);
    animation_manager.tick(time);
}

void MovingPlatform::check_map_collisions(GameMap &game_map, DIRECTION dir) {
    for (int i = get_y() / h ; i < (get_y() + h) / h; ++i) {
        for (int j = get_x() / w; j < (get_x() + w) / w; ++j) {
            if (game_map.char_map[i][j] == 'B'){
                if ((dx > 0) && (dir == HORIZONTAL)) {
                    set_x(j * w - w);
                }
                if ((dx < 0) && (dir == HORIZONTAL)) {
                    set_x(j * w + w);
                }
                set_dx(-get_dx());
                if ((dy > 0) && (dir == VERTICAL)) {
                    set_y(i * h - h);
                    set_dy(0);
                }
                if ((dy < 0) && (dir == VERTICAL)) {
                    set_y(i * h + h);
                    set_dy(0);
                }
            }
        }
    }
}

void MovingPlatform::set_animations() {
    animation_manager.create("moving_platform", texture, 0, 0, get_w(), get_h(), 1, 0, 0);
}

#endif //MOVINGPLATFORM_H_


