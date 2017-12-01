#ifndef HEALTH_BAR_H_
#define HEALTH_BAR_H_

#include <string>

const int HEALTH_RECT_OFFSET_X = 105;
const int HEALTH_RECT_OFFSET_Y = 38;
const int HEALTH_RECT_BORDER_THICKNESS = 2;
const int HEALTH_RECT_WIDTH = 48;
const int HEALTH_RECT_LENGTH = 16;

class HealthBar {
public:
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    std::string name;
    int max_health;
    sf::RectangleShape health_rect;
    sf::RectangleShape background_rect;
    sf::RectangleShape rect_border;
    HealthBar(const std::string &m_name, int m_max_health) {
        name = m_name;
        max_health = m_max_health;
        rect_border.setFillColor(sf::Color::Black);
        rect_border.setOutlineThickness(HEALTH_RECT_BORDER_THICKNESS);
        rect_border.setPosition(HEALTH_RECT_OFFSET_X, HEALTH_RECT_OFFSET_Y);
        rect_border.setSize({HEALTH_RECT_WIDTH, HEALTH_RECT_LENGTH});
        health_rect.setFillColor(sf::Color(50, 200, 100));
        health_rect.setPosition(HEALTH_RECT_OFFSET_X + HEALTH_RECT_BORDER_THICKNESS, HEALTH_RECT_OFFSET_Y + HEALTH_RECT_BORDER_THICKNESS);
        health_rect.setSize({HEALTH_RECT_WIDTH - 2 * HEALTH_RECT_BORDER_THICKNESS, HEALTH_RECT_LENGTH - 2 * HEALTH_RECT_BORDER_THICKNESS});
        health_rect.setPosition(HEALTH_RECT_OFFSET_X + HEALTH_RECT_BORDER_THICKNESS, HEALTH_RECT_OFFSET_Y + HEALTH_RECT_BORDER_THICKNESS);
        health_rect.setSize({HEALTH_RECT_WIDTH - 2 * HEALTH_RECT_BORDER_THICKNESS, HEALTH_RECT_LENGTH - 2 * HEALTH_RECT_BORDER_THICKNESS});
    }
    void update(int current_health);
    void draw(sf::RenderWindow &window);
};

void HealthBar::update(int current_health) {
    double rect_width = (HEALTH_RECT_WIDTH - 2 * HEALTH_RECT_BORDER_THICKNESS) * current_health / max_health;
    double rect_height = HEALTH_RECT_LENGTH - 2 * HEALTH_RECT_BORDER_THICKNESS;
    health_rect.setSize({rect_width, rect_height});
    background_rect.setPosition({HEALTH_RECT_OFFSET_X + HEALTH_RECT_BORDER_THICKNESS + rect_width, HEALTH_RECT_OFFSET_Y + HEALTH_RECT_BORDER_THICKNESS});
    background_rect.setSize({HEALTH_RECT_WIDTH - rect_width - 2 * HEALTH_RECT_BORDER_THICKNESS, HEALTH_RECT_LENGTH - 2 * HEALTH_RECT_BORDER_THICKNESS});
}

void HealthBar::draw(sf::RenderWindow& window) {
    window.draw(rect_border);
    window.draw(health_rect);
    window.draw(background_rect);
}

#endif // HEALTH_BAR_H_
