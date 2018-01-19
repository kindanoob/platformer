#ifndef PLAYER_H_
#define PLAYER_H_

#include "entity.h"

const int INVUL_DURATION = 2000;//in milliseconds, time during which character is invulnerable after contact with enemy (if character survived the contact)
const int INVUL_DURATION_DELAY = 500;//time after contact with enemy during which player cannot control the character
const int INVUL_NO_CONTROL_DURATION = 500;//in milliseconds, time period after contact with enemy during which user cannot control
                                          //player using keyboard
const double SPEED_X = 0.15;
const double SPEED_Y = 0.33;
const double GRAVITY_CONST = 0.0005;
const int MAX_HEALTH = 300;
const double EPSILON = 0.000001;
const double GRAVITY_ON_GROUND = 0.1;//gravity force that applies to character when he is on the ground
const int NUM_WEAPONS = 2;
const int FIRE_DAMAGE = 10;


class Player: public Entity {
public:
    enum STATE {
        WALK_LEFT, 
        WALK_RIGHT, 
        STAY_LEFT, 
        STAY_RIGHT, 
        IN_AIR_LEFT, 
        IN_AIR_RIGHT
    };
    enum WEAPON_TYPE {
        NO_WEAPON, 
        PISTOL, 
        ROCKET, 
        MACHINE_GUN
    };
    int score;
    bool is_invulnerable;
    int invul_duration;
    bool on_ground;
    STATE state;
    bool on_platform;
    bool has_weapon;
    WEAPON_TYPE current_weapon;
    bool is_shooting;
    int max_health;
    bool left_right_pressed;
    int dead_duration;
    double blink_animation_speed;
    std::array<bool, NUM_WEAPONS> weapons;
    Player(const sf::Texture &m_texture, const std::string &m_name, double m_x, double m_y, double m_w, double m_h, int row, int col):
        Entity(m_texture, m_name, m_x, m_y, m_w, m_h, row, col) {
            score = 0;
            is_invulnerable = false;
            invul_duration = 0;
            health = MAX_HEALTH;
            on_ground = false;//in the beginning player spawns in the air and falls on the ground
            on_platform = false;
            left_right_pressed = false;
            has_weapon = false;
            is_shooting = false;
            max_health = MAX_HEALTH;
            current_weapon = NO_WEAPON;
            std::fill(weapons.begin(), weapons.end(), false);
            weapons[0] = true;//character always has NO_WEAPON weapon
            dead_duration = 0;
            blink_animation_speed = 0.01;
            set_animations();
            //set initial position of character
            animation_manager.set_animation("player_stay_right");
    }
    void process_keyboard_input();
    void collision(DIRECTION dir);
    void check_map_collisions (GameMap &game_map, DIRECTION dir);
    void update(double time, GameMap &game_map, double offset_x, double offset_y);
    void update_current_animation();
    void set_animations();
};

void Player::process_keyboard_input() {
    left_right_pressed = false;
    if (get_is_alive() && (invul_duration < INVUL_DURATION - INVUL_DURATION_DELAY)) {
        //set the default state for the character, it may be changed depending on keyboard input
        if (on_ground || on_platform) {
            if (get_dx_prev() > 0) {
                state = STAY_RIGHT;
            } else {
                state = STAY_LEFT;
            }
        } else {
            if (get_dx_prev() > 0) {
                state = IN_AIR_RIGHT;
            } else {
                state = IN_AIR_LEFT;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            left_right_pressed = true;
            if (0) {
                set_dx(get_dx() - SPEED_X);
            } else {
                set_dx(-SPEED_X);
            }
            state = WALK_LEFT;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            left_right_pressed = true;
            if (0) {
                set_dx(get_dx() + SPEED_X);
            } else {
                set_dx(SPEED_X);
            }
            state = WALK_RIGHT;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (on_ground || on_platform) {
                set_dy(-SPEED_Y);
                on_ground = false;
                on_platform = false;
                if (get_dx_prev() > 0) {
                    state = IN_AIR_RIGHT;
                } else {
                    state = IN_AIR_LEFT;
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            current_weapon = NO_WEAPON;
            has_weapon = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            if (weapons[1]) {
                current_weapon = PISTOL;
                has_weapon = true;
            }
        }
    } else {
        //
    }
}

void Player::check_map_collisions (GameMap &game_map, DIRECTION dir) {
    if (!is_alive) {
        return;
    }
    if (get_y() + get_h() > game_map.ground_level) {
        is_alive = false;
        health = 0;
        //std::cout << "below ground" << std::endl;
        return;
    }
    for (int i = get_y() / h ; i < (get_y() + get_h()) / get_h(); ++i) {
        for (int j = get_x() / h; j < (get_x() + rect.width) / get_h(); ++j) {
            if (game_map.char_map[i][j] == 'B') {
                if ((get_dx() > 0) && (dir == HORIZONTAL)) {
                    set_x(j * h - w);
                }
                if ((get_dx() < 0) && (dir == HORIZONTAL)) {
                    set_x(j * h + h);
                }
                if ((get_dy() > 0) && (dir == VERTICAL)) {
                    set_y(i * h - h);
                    dy = 0.0;
                    on_ground = true;
                }
                if ((get_dy() < 0) && (dir == VERTICAL)) {
                    set_y(i * h + h);
                    set_dy(0);
                }
            } else if (game_map.char_map[i][j] == '0') {
                game_map.char_map[i][j] = ' ';
                ++score;
            } else if (game_map.char_map[i][j] == 'P') {
                weapons[1] = true;
                game_map.char_map[i][j] = ' ';
            } else if (game_map.char_map[i][j] == 'D') {
                if (invul_duration == 0) {//character is vulnerable to damage
                    invul_duration = INVUL_DURATION;//in milliseconds
                    health -= std::min(health, FIRE_DAMAGE);
                    if (health == 0) {
                        is_alive = false;
                        return;
                    }
                    set_dy(-0.2);
                    set_dx(0.1);
                    if (fabs(get_dx_prev()) > 0.0001) {
                        set_dx(get_dx() * (-get_dx_prev() / fabs(get_dx_prev())));
                    } else {
                        //
                    }
                } else {
                    //invul_duration -= std::min(invul_duration, time);//in milliseconds
                }
            }
        }
    }
}

//updates current animation depending on the current player state
void Player::update_current_animation() {
    if (current_weapon != NO_WEAPON) {
        switch(state) {
            case STAY_LEFT: {
                animation_manager.set_animation("player_shoot_stay_left");
                if (invul_duration > 0) {
                    animation_manager.set_animation("player_shoot_stay_left_blink");
                }
                break;
            }
            case STAY_RIGHT: {
                animation_manager.set_animation("player_shoot_stay_right");
                if (invul_duration > 0) {
                    animation_manager.set_animation("player_shoot_stay_right_blink");
                }
                break;
            }
            case WALK_LEFT: {
                animation_manager.set_animation("player_shoot_walk_left");
                if (invul_duration > 0) {
                    animation_manager.set_animation("player_shoot_walk_left_blink");
                }
                break;
            }
            case WALK_RIGHT: {
                animation_manager.set_animation("player_shoot_walk_right");
                if (invul_duration > 0) {
                    animation_manager.set_animation("player_shoot_walk_right_blink");
                }
                break;
            }
            case IN_AIR_LEFT: {
                animation_manager.set_animation("player_shoot_in_air_left");
                if (invul_duration > 0) {
                    animation_manager.set_animation("player_shoot_in_air_left_blink");
                }
                break;
            }
            case IN_AIR_RIGHT: {
                animation_manager.set_animation("player_shoot_in_air_right");
                if (invul_duration > 0) {
                    animation_manager.set_animation("player_shoot_in_air_right_blink");
                }
                break;
            }
        }
    } else {
        switch(state) {
            case STAY_LEFT: {
                animation_manager.set_animation("player_stay_left");
                if (invul_duration > 0) {
                    animation_manager.set_animation("player_stay_left_blink");
                }
                break;
            }
            case STAY_RIGHT: {
                animation_manager.set_animation("player_stay_right");
                if (invul_duration > 0) {
                    animation_manager.set_animation("player_stay_right_blink");
                }
                break;
            }
            case WALK_LEFT: {
                if (invul_duration > 0) {
                    animation_manager.set_animation("player_walk_left_blink");
                }
                else {
                    animation_manager.set_animation("player_walk_left");
                }
                break;
            }
            case WALK_RIGHT: {
                animation_manager.set_animation("player_walk_right");
                if (invul_duration > 0) {
                    animation_manager.set_animation("player_walk_right_blink");
                }
                break;
            }
            case IN_AIR_LEFT: {
                animation_manager.set_animation("player_in_air_left");
                if (invul_duration > 0) {
                    animation_manager.set_animation("player_in_air_left_blink");
                }
                break;
            }
            case IN_AIR_RIGHT: {
                animation_manager.set_animation("player_in_air_right");
                if (invul_duration > 0) {
                    animation_manager.set_animation("player_in_air_right_blink");
                }
                break;
            }
        }
    }
}


void  Player::update(double time, GameMap &game_map, double offset_x, double offset_y) {
    set_x(get_x() + dx * time);
    check_map_collisions(game_map, HORIZONTAL);

    if (!on_ground) {
        set_dy(get_dy() + GRAVITY_CONST * time);//if character is in the air, apply gravity to him
        set_y(get_y() + dy * time);//update characters y coordinate depending on it's vertical velocity
    } else {
        if (invul_duration > 1900) {
        }
    }
    if (!is_alive) {
        dead_duration += time;
        return;
    }

    on_ground = false;
    check_map_collisions(game_map, VERTICAL);

    if (invul_duration > 0) {
        invul_duration -= std::min(static_cast<double>(invul_duration), time);
        update_current_animation();
        animation_manager.tick(time);
        if (invul_duration > INVUL_DURATION - INVUL_NO_CONTROL_DURATION) {
            return;
        }
    }
    //if (rect.top > GROUND) { rect.top = GROUND; dy = 0; on_ground = true;}
    //current_frame += 0.005 * time;
    //if (current_frame > 4) current_frame -= 4 ;
    if ((fabs(dy) > EPSILON) && (fabs(dy) < 0.3) && !on_platform) {//if character is in air and sufficiently above the ground level
        if (dx_prev > 0) {//if last movement in along x axis was in the right direction
            //sprite.setTextureRect(sf::IntRect(w * 0, h * 0, w, h));
            //animation_manager.set_animation("player_in_air_right");
            state = IN_AIR_RIGHT;
        } else {//if last movement in along x axis was in the left direction
            //sprite.setTextureRect(sf::IntRect(w * 0, h * 1, w, h));
            //animation_manager.set_animation("player_in_air_left");
            state = IN_AIR_LEFT;
        }
    } else if (fabs(dx) < 0.0001) {//if character is on the ground (or near ground) and is not moving along x axis
        if (dx_prev > 0) {
            //sprite.setTextureRect(sf::IntRect(1 * w, 0 * h, w, h));
            //animation_manager.set_animation("player_stay_right");
            state = STAY_RIGHT;
        } else {
            //sprite.setTextureRect(sf::IntRect(1 * w, 1 * h, w, h));
            //animation_manager.set_animation("player_stay_left");
            state = STAY_LEFT;
        }
    } else if (dx > 0) {
        //sprite.setTextureRect(sf::IntRect(w * static_cast<int>(current_frame), 0, w, h));
        //animation_manager.set_animation("player_walk_right");
        //state = WALK_RIGHT;
        //std::cout << "player_walk_right" << std::endl;
    } else if (dx < 0) {
        //sprite.setTextureRect(sf::IntRect(w * static_cast<int>(current_frame), 32, w, h));
        //animation_manager.set_animation("player_walk_left");
        //state = WALK_LEFT;
    }
    update_current_animation();
    animation_manager.tick(time);

    //if character is moving along x axis, update dx_prev,
    //update it only if left or right key was pressed
    if ((fabs(dx) > 0.0001) && left_right_pressed) {        
        set_dx_prev(get_dx());
    }
    set_dx(0);
    on_platform = false;
}

void Player::set_animations() {
    animation_manager.create("player_stay_left", texture, 0 * w, h, w, h, 1, 0.005, w);
    animation_manager.create("player_stay_right", texture, 0 * w, 0 * h, w, h, 1, 0.005, w);
    animation_manager.create("player_walk_left", texture, 0 * w, h, w, h, 4, 0.005, w);
    animation_manager.create("player_walk_right", texture, 0 * w, 0 * h, w, h, 4, 0.005, w);
    animation_manager.create("player_in_air_left", texture, 1 * w, h, w, h, 1, 0.005, w);
    animation_manager.create("player_in_air_right", texture, 1 * w, 0 * h, w, h, 1, 0.005, w);

    animation_manager.create("player_stay_left_blink", texture, 0 * w, 5 * h, w, h, 2, blink_animation_speed, w);
    animation_manager.create("player_stay_right_blink", texture, 0 * w, 4 * h, w, h, 2, blink_animation_speed, w);
    animation_manager.create("player_walk_left_blink", texture, 0 * w, 5 * h, w, h, 8, blink_animation_speed, w);
    animation_manager.create("player_walk_right_blink", texture, 0 * w, 4 * h, w, h, 8, blink_animation_speed, w);
    animation_manager.create("player_in_air_left_blink", texture, 2 * w, 5 * h, w, h, 2, blink_animation_speed, w);
    animation_manager.create("player_in_air_right_blink", texture, 2 * w, 4 * h, w, h, 2, blink_animation_speed, w);

    animation_manager.create("player_shoot_stay_left", texture, 0 * w, 3 * h, w, h, 1, 0.005, w);
    animation_manager.create("player_shoot_stay_right", texture, 0 * w, 2 * h, w, h, 1, 0.005, w);
    animation_manager.create("player_shoot_walk_left", texture, 0 * w, 3 * h, w, h, 4, 0.005, w);
    animation_manager.create("player_shoot_walk_right", texture, 0 * w, 2 * h, w, h, 4, 0.005, w);
    animation_manager.create("player_shoot_in_air_left", texture, 1 * w, 3 * h, w, h, 1, 0.005, w);
    animation_manager.create("player_shoot_in_air_right", texture, 1 * w, 2 * h, w, h, 1, 0.005, w);

    animation_manager.create("player_shoot_stay_left_blink", texture, 0 * w, 7 * h, w, h, 2, 0.005, w);
    animation_manager.create("player_shoot_stay_right_blink", texture, 0 * w, 6 * h, w, h, 2, 0.005, w);
    animation_manager.create("player_shoot_walk_left_blink", texture, 0 * w, 7 * h, w, h, 8, 0.005, w);
    animation_manager.create("player_shoot_walk_right_blink", texture, 0 * w, 6 * h, w, h, 8, 0.005, w);
    animation_manager.create("player_shoot_in_air_left_blink", texture, 2 * w, 7 * h, w, h, 2, 0.005, w);
    animation_manager.create("player_shoot_in_air_right_blink", texture, 2 * w, 6 * h, w, h, 2, 0.005, w);
    //animation_manager.create("player_died", player.texture, 1 * player.w, player.h, player.w, player.h, 1, 0.005, player.w);
}

#endif // PLAYER_H_
