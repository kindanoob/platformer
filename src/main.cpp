#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <list>
#include <iterator>

#include "config.h"
#include "player.h"
#include "enemy.h"
#include "moving_platform.h"
#include "animation_manager.h"
#include "view.h"
#include "bullet.h"
#include "health_bar.h"
#include "menu.h"
#include "map_obstacle.h"
#include "window.h"
#include "resource_holder.h"
#include "texture_manager.h"

double offset_x = 0;
double offset_y = 0;


class Game {
public:
    std::list<Entity*> entities_list;
    sf::RenderWindow game_window;
    Game();
};



void draw_map(sf::RenderWindow &window, const std::vector<std::string> &tile_map) {
    for (size_t i = 0; i < tile_map.size(); i++) {
         for (size_t j = 0; j < tile_map[0].length(); j++) {
             sf::RectangleShape rectangle(sf::Vector2f(32, 32));
             if (tile_map[i][j] == 'B') rectangle.setFillColor(sf::Color::Black);
             else if (tile_map[i][j] == '0')  rectangle.setFillColor(sf::Color::Green);
             else if (tile_map[i][j] == 'P')  rectangle.setFillColor(sf::Color::Yellow);
             else if (tile_map[i][j] == 'D')  rectangle.setFillColor(sf::Color::Red);
             else if (tile_map[i][j] == ' ') continue;
             rectangle.setPosition(j * 32 - offset_x, i * 32 - offset_y) ;
             window.draw(rectangle);
         }
    }
}

void update_offset_x(const Entity &entity, const GameMap &game_map) {
    if ((entity.get_x() > SCREEN_WIDTH / 2) && (entity.get_x() < game_map.width * game_map.tile_side_length - SCREEN_WIDTH / 2 )) {
            offset_x = entity.get_x() - SCREEN_WIDTH / 2;
    }
}

void update_offset_y(const Entity &entity) {
    if (entity.get_y() > SCREEN_HEIGHT / 2) {
            //offsetY = p.rect.top - SCREEN_WIDTH / 2;
    }
}

void check_intersection_with_enemy(Player &player, Enemy &enemy) {
    if (player.get_rect().intersects(enemy.get_rect())) {
        if (enemy.is_alive && player.is_alive && (abs(player.invul_duration) == 0)) {
            //if player is falling on the ground and he is above the enemy
            if ((player.dy > 0) && (player.get_y() + player.get_h() * 3 / 4 < enemy.get_y())) {
                
                enemy.dx = 0;
                player.dy = -0.2;
                enemy.is_alive = false;
                enemy.sprite.setColor(sf::Color::Red);
                enemy.dy = 0.5;
            } else if ((enemy.damage > 0) && (player.health > enemy.damage)) {//else if (fabs(player.invul_duration) < 0.0001)
                player.health -= enemy.damage;
                if (player.health <= 0) {
                    //GAME OVER;
                }
                player.invul_duration = INVUL_DURATION;//in milliseconds
                //BLINK ANIMATION, invulnerable for 2 seconds
                player.dy = -0.2;
                player.dx = 1.25 * fabs(enemy.dx);
                if (fabs(player.dx_prev) > 0.0001) {
                    player.dx *= -player.dx_prev / fabs(player.dx_prev);
                } else {
                    player.dx = enemy.dx;
                }
            } else {
                player.health -= std::min(player.health, enemy.damage);
                player.is_alive = false;
                player.dy = 0.3;
                player.sprite.setColor(sf::Color::Red);
            }
        }
    }
}

void check_intersection_with_moving_platform(Player &player, MovingPlatform &mp) {
    if (player.get_rect().intersects(mp.get_rect())) {
        if ((player.get_y() + player.get_h() < mp.get_y() + 5) &&
           (player.get_dx() + player.get_w() / 2 > mp.get_dx()) &&
           (player.get_dx() + player.get_w() / 2 < mp.get_dx() + mp.get_h())) {
            player.set_y(mp.get_y() - player.get_h());
            player.set_dy(0);
            player.on_platform = true;
            player.set_dx(mp.get_dx());
        } else if ((player.get_y() > mp.get_y() + mp.get_h() - 5) &&
               (player.get_dx() + player.get_w() / 2 > mp.get_dx()) &&
               (player.get_dx() + player.get_w() / 2 < mp.get_dx() + mp.get_h())) {
            player.set_y(mp.get_y() + mp.get_h());
            player.set_dy(0.075);
        } else if (player.get_x() < mp.get_x()) {//if character is to the left of the platform
            player.set_x(mp.get_x() - player.get_w());
        } else if (player.get_x() + player.get_w() > mp.get_x() + mp.get_w()) {//if character is to the right of the platform
            player.set_x(mp.get_x() + mp.get_w());
        }
    }
}


class My_text {
public:
    sf::Text text;
    sf::Font font;
    My_text(const std::wstring &s, const sf::Font &font, unsigned int font_size,
            const sf::Color &text_color, const sf::Uint32 &text_style, int pos_x, int pos_y) {
        text.setString(s);
        text.setFont(font);
        text.setCharacterSize(font_size);
        text.setColor(text_color);
        text.setPosition(sf::Vector2f(pos_x, pos_y));
        text.setStyle(text_style);
    }
};


int main() {
    std::list<Enemy *> enemies_list;
    std::list<Bullet *> bullets_list;
    std::list<Bullet *> obstacles_list;
    std::list<MovingPlatform *> mov_plat_list;
    GameView game_view(SCREEN_WIDTH, SCREEN_HEIGHT);
    sf::View game_camera = game_view.game_camera;


    sf::RenderWindow window;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Platformer", sf::Style::Default);
    show_menu(window);
    GameMap game_map(2);


    Resource_holder resource_holder;

    sf::Texture player_texture = resource_holder.textures.get_resource(Texture_name::player_texture);
    
    Player player(player_texture, "Player", 7 * 32, 5 * 32, 24, 32, 0, 1);

    sf::Texture basic_enemy_texture = resource_holder.textures.get_resource(Texture_name::basic_enemy_texture);
    Enemy *basic_enemy_1 = new Enemy(basic_enemy_texture, "basic_enemy", 32 * 11, 32 * 10, 32, 32, 1, 1);
    enemies_list.push_back(basic_enemy_1);
    Enemy *basic_enemy_2 = new Enemy(basic_enemy_texture, "basic_enemy", 32 * 17, 32 * 10, 32, 32, 1, 1);
    enemies_list.push_back(basic_enemy_2);
    Enemy *basic_enemy_3 = new Enemy(basic_enemy_texture, "basic_enemy", 32 * 21, 32 * 10, 32, 32, 1, 1);
    enemies_list.push_back(basic_enemy_3);
    Enemy *basic_enemy_4 = new Enemy(basic_enemy_texture, "basic_enemy", 32 * 27, 32 * 10, 32, 32, 1, 1);
    enemies_list.push_back(basic_enemy_4);
    Enemy *basic_enemy_5 = new Enemy(basic_enemy_texture, "basic_enemy", 32 * 35, 32 * 10, 32, 32, 1, 1);
    enemies_list.push_back(basic_enemy_5);
    Enemy *basic_enemy_6 = new Enemy(basic_enemy_texture, "basic_enemy", 32 * 42, 32 * 8, 32, 32, 1, 1);
    enemies_list.push_back(basic_enemy_6);
    Enemy *basic_enemy_7 = new Enemy(basic_enemy_texture, "basic_enemy", 32 * 65, 32 * 6, 32, 32, 1, 1);
    enemies_list.push_back(basic_enemy_7);
    Enemy *basic_enemy_8 = new Enemy(basic_enemy_texture, "basic_enemy", 32 * 82, 32 * 4, 32, 32, 1, 1);
    enemies_list.push_back(basic_enemy_8);
    Enemy *basic_enemy_9 = new Enemy(basic_enemy_texture, "basic_enemy", 32 * 11, 32 * 2, 32, 32, 1, 1);
    enemies_list.push_back(basic_enemy_9);

    sf::Texture fire_texture = resource_holder.textures.get_resource(Texture_name::fire_texture);
    Map_obstacle *fire_obstacle_1 = new Map_obstacle(fire_texture, "fire_obstacle", 32 * 3, 32 * 7, 32, 32, 0, 0);



    
    sf::Texture moving_platform_texture = resource_holder.textures.get_resource(Texture_name::moving_platform_texture);
    MovingPlatform *moving_platform0 = new MovingPlatform(moving_platform_texture, "moving_platform", 32 * 7, 32 * 5, 32 * 3, 32, 0, 0);
    MovingPlatform *moving_platform1 = new MovingPlatform(moving_platform_texture, "moving_platform", 32 * 177, 32 * 5, 32 * 3, 32, 0, 0);
    mov_plat_list.push_back(moving_platform0);
    mov_plat_list.push_back(moving_platform1);
    
    
    sf::Texture bullet_texture = resource_holder.textures.get_resource(Texture_name::bullet_texture);

    HealthBar player_health_bar("player_health_bar", player.max_health);

    sf::Clock clock;
    sf::Clock game_time_clock;


    double gameTime = 0;//accumulates time passed since the game started

    int fps_count = -1;

    window.setVerticalSyncEnabled(true);


    sf::Font ubuntu_font = resource_holder.fonts.get_resource(Font_name::ubuntu_font);
    sf::Font arial_font = resource_holder.fonts.get_resource(Font_name::arial_font);
    sf::Font cyrillic_font = resource_holder.fonts.get_resource(Font_name::cyrillic_font);
    

    sf::Text game_info_text("", ubuntu_font, 20);
    game_info_text.setColor(sf::Color::Black);
    game_info_text.setPosition(32, 32);

    sf::Text game_timer_text("", ubuntu_font, 20);
    game_timer_text.setColor(sf::Color::Black);
    game_timer_text.setPosition(600, 32 * 15);

    int cnt = 10;
    while (window.isOpen()) {
        int time = clock.getElapsedTime().asMicroseconds();
        if (time % 10 == 0) {
            fps_count = 1000000.0 / time;
        }
        if (player.is_alive) {
            gameTime = game_time_clock.getElapsedTime().asSeconds();
            //std::cout << time << ", " << gameTime << std::endl;
            //std::cout << "FPS: " << 1000000.0 / time << std::endl;
        }
        clock.restart();
        time /= TIME_ADJUSTMENT;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Z) {
                    if (player.has_weapon) {
                        player.is_shooting = true;
                    }
                }
            }
        }
        if (player.is_shooting) {
            player.is_shooting = false;
            int bullet_direction = 1;//default direction is RIGHT
            int bullet_x = player.get_x() + player.get_w();
            int bullet_y = player.get_y() + 5;
            if (player.dx_prev < 0) {
                bullet_direction = 0;
                bullet_x -= player.get_w();
            }
            Bullet* bullet = new Bullet(bullet_texture, "bullet", bullet_x, bullet_y, 4, 4, 0, 0, bullet_direction);
            bullets_list.push_back(bullet);
        }
        player.process_keyboard_input();
        player.update(time, game_map, offset_x, offset_y);
        for (auto e: enemies_list) {
            e->update(time, game_map, offset_x, offset_y);
            check_intersection_with_enemy(player, *e);
            if (!player.is_alive) {

            }
        }
        for (auto b: bullets_list) {
            b->update(time, game_map, offset_x, offset_y);
        }

        for (auto &e: mov_plat_list) {
            e->update(time, game_map, offset_x, offset_y);
            check_intersection_with_moving_platform(player, *e);
        }
        
        player_health_bar.update(player.health);

        
        game_view.update_camera_view(player.get_x(), player.get_y(), game_map.width, game_map.height);
        window.setView(game_camera);

        update_offset_x(player, game_map);
        update_offset_y(player);
        window.clear(sf::Color::White);
        draw_map(window, game_map.char_map);



        std::string game_fps_string = std::to_string(fps_count);

	    std::ostringstream playerScoreString;
        std::ostringstream playerHealthString, gameTimeString;
        playerScoreString << player.score;
        gameTimeString << static_cast<int>(gameTime);

        game_info_text.setString("Health " + playerHealthString.str() + "\nApples collected: " + playerScoreString.str());
        game_timer_text.setString("Game timer: " + gameTimeString.str() + "\nFPS: " + game_fps_string);
        window.draw(game_info_text);
        window.draw(game_timer_text);
        

        ///DRAWING_BLOCK
        if (player.dead_duration < 2000) {
            player.draw(window, offset_x, offset_y);
        } else {
            window.close();
        }
        for (auto it = enemies_list.begin(); it != enemies_list.end();) {
            if ((*it)->dead_duration < 2) {
                for (auto it2 = bullets_list.begin(); it2 != bullets_list.end();) {
                    if (((*it2)->is_alive) && ((*it)->get_rect().intersects((*it2)->get_rect()))) {
                        (*it)->health -= (*it2)->damage;
                        if ((*it)->health <= 0) {
                            (*it)->is_alive = false;
                        }
                        (*it2)->is_alive = false;
                        Bullet *temp = *it2;
                        it2 = bullets_list.erase(it2);
                        delete(temp);
                    } else {
                        (*it2)->draw(window, offset_x, offset_y);
                        ++it2;
                    }
                }
                (*it)->draw(window, offset_x, offset_y);
                ++it;
            }
            else {
                Enemy *temp = *it;
                it = enemies_list.erase(it);
                delete(temp);
            }
        }
        for (auto it = bullets_list.begin(); it != bullets_list.end();) {
            if ((*it)->is_alive) {
                (*it)->draw(window, offset_x, offset_y);
                ++it;
            } else {
                Bullet *temp = *it;
                it = bullets_list.erase(it);
                delete(temp);
            }
        }
        for (auto &e: mov_plat_list) {
            e->draw(window, offset_x, offset_y);
        }
        player_health_bar.draw(window);
        //fire_obstacle_1->update(time, game_map, offset_x, offset_y);
        //fire_obstacle_1->draw(window, offset_x, offset_y);
        window.display();
    }
    return 0;
}
