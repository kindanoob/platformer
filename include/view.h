#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SFML/Graphics.hpp>

const double MAP_SCROLL_SPEED = 0.1;

class GameView {
public:
    int screen_width;
    int screen_height;
    double offset_x;
    double offset_y;
    GameView(int m_screen_width, int m_screen_height);
    sf::View game_camera;
    void update_camera_view(double x, double y, int map_width, int map_height);
    void scroll_camera(double time);
    void apply_camera_effects();
};

GameView::GameView(int m_screen_width, int m_screen_height) {
    screen_width = m_screen_width;
    screen_height = m_screen_height;
    game_camera.reset(sf::FloatRect(0, 0, screen_width, screen_height));
}


void GameView::update_camera_view(double x, double y, int map_width, int map_height) {
    if ((x > screen_width / 2) && (x < map_width * 32 - screen_width / 2 )){
            offset_x = x - screen_width / 2;
    }
    if (y > screen_height / 2){
        offset_y = y - screen_height / 2;
    }
    int new_camera_x_coord = x;
    int new_camera_y_coord = y;
    if((x < screen_width / 2) || (x > map_width * 32 - screen_width / 2)){
        new_camera_x_coord = screen_width / 2;
    }
    if((y < screen_height / 2) || (y > map_height * 32 - screen_height / 2)){
        new_camera_y_coord = screen_height / 2;
    }
    game_camera.setCenter(new_camera_x_coord, new_camera_y_coord);
}

void GameView::scroll_camera(double time) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		game_camera.move(0, MAP_SCROLL_SPEED * time);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		game_camera.move(-MAP_SCROLL_SPEED * time, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		game_camera.move(0, MAP_SCROLL_SPEED * time);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		game_camera.move(MAP_SCROLL_SPEED * time, 0);
	}
}

void GameView::apply_camera_effects() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
		game_camera.zoom(1.0100f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		game_camera.rotate(1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		game_camera.setSize(640, 480);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		game_camera.setSize(540, 380);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		game_camera.setViewport(sf::FloatRect(0, 0, 0.5f, 1));
    }
}


#endif // VIEW_H
