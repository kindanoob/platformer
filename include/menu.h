#ifndef MENU_H_
#define MENU_H_

#include "config.h"


const int MENU_TITLE_TEXT_SIZE = 70;
const int OPTIONS_TITLE_TEXT_SIZE = 50;
const int OPTIONS_REGULAR_TEXT_SIZE = 30;
const int MENU_TEXT_SIZE = 30;
const int kMenuReturnBackTextSize = 30;
const double VERTICAL_OFFSET_TOP_COEFF = 0.65;
const int border_thickness = 4;//in pixels

void show_options_screen(sf::RenderWindow &window) {
    int screen_width = window.getSize().x;
    int screen_height = window.getSize().y;
    int options_height = screen_height / 2;
    int options_width = 0;
    bool show_options = true;
    sf::Font options_font;
    options_font.loadFromFile(fonts_path + "/ubuntu.ttf");
    sf::Text options_text_title("Options", options_font, MENU_TITLE_TEXT_SIZE);    
    sf::FloatRect options_text_title_rect = options_text_title.getLocalBounds();
    int offset_y_top = screen_height;
    options_text_title.setPosition((screen_width - options_text_title_rect.width) / 2, (offset_y_top - options_text_title_rect.height) / 2);
    options_text_title.setColor(sf::Color::Black);
    sf::Text options_go_back_text("Press Escape to return to main menu.", options_font, kMenuReturnBackTextSize);
    options_go_back_text.setColor(sf::Color::Black);
    options_go_back_text.setPosition(options_text_title.getPosition() + sf::Vector2f(0, MENU_TITLE_TEXT_SIZE * 1.5));

    while (show_options) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            show_options = false;
        }
        window.clear(sf::Color(30, 110, 190));
        options_text_title.setPosition((screen_width - options_text_title_rect.width) / 2, (offset_y_top - options_text_title_rect.height) / 2);
        window.draw(options_text_title);
        window.draw(options_go_back_text);
        window.display();
    }
}

int show_menu(sf::RenderWindow &window) {
    int screen_width = window.getSize().x;
    int screen_height = window.getSize().y;
    int menu_width = screen_width * 0.3;
    int offset_x = (screen_width / 2 - menu_width) / 2;
    int menu_height = screen_height / 2;
    int offset_y_top = (screen_height - menu_height) * VERTICAL_OFFSET_TOP_COEFF;
    int offset_y_bottom = (screen_height - menu_height) * (1 - VERTICAL_OFFSET_TOP_COEFF);
    int button_width = menu_width - 2 * border_thickness;
    int button_height = (menu_height - 4 * border_thickness) / 3;
    int button_height_remainder = (menu_height - 4 * border_thickness) % 3;
    sf::RectangleShape background_rect;
    background_rect.setFillColor(sf::Color::Black);
    background_rect.setSize({menu_width, menu_height});
    background_rect.setPosition({screen_width / 2 + offset_x, offset_y_top});
    sf::RectangleShape new_game_button;
    new_game_button.setFillColor(sf::Color::White);
    int new_game_button_height = button_height + std::max(0, button_height_remainder);
    new_game_button.setSize({button_width, new_game_button_height});
    --button_height_remainder;
    new_game_button.setPosition({screen_width / 2 + offset_x + border_thickness, offset_y_top + border_thickness});
    sf::RectangleShape options_button;
    options_button.setFillColor(sf::Color::White);
    int options_button_height = button_height + std::max(0, button_height_remainder);
    options_button.setSize({button_width, options_button_height});
    --button_height_remainder;
    options_button.setPosition({screen_width / 2 + offset_x + border_thickness, offset_y_top + new_game_button_height + 2 * border_thickness});
    sf::RectangleShape quit_game_button;
    quit_game_button.setFillColor(sf::Color::White);
    int quit_button_height = button_height + std::max(0, button_height_remainder);
    quit_game_button.setSize({button_width, quit_button_height});
    quit_game_button.setPosition({screen_width / 2 + offset_x + border_thickness, offset_y_top + new_game_button_height + options_button_height + 3 * border_thickness});

    sf::Font menu_font;
    menu_font.loadFromFile(fonts_path + "/ubuntu.ttf");
    sf::Text new_game_text("New game", menu_font, MENU_TEXT_SIZE);
    sf::FloatRect new_game_text_rect = new_game_text.getLocalBounds();
    new_game_text.setColor(sf::Color::Black);
    
    new_game_text.setPosition(sf::Vector2f(screen_width / 2 + offset_x + border_thickness + (button_width - new_game_text_rect.width) / 2,
                                           offset_y_top + border_thickness + (new_game_button_height - new_game_text_rect.height) / 2));
    sf::Text options_text("Options", menu_font, MENU_TEXT_SIZE);
    sf::FloatRect options_text_rect = options_text.getLocalBounds();
    options_text.setPosition(sf::Vector2f(screen_width / 2 + offset_x + border_thickness + (button_width - new_game_text_rect.width) / 2,
                                           offset_y_top + 2 * border_thickness + new_game_button_height + (options_button_height - options_text_rect.height) / 2));
    options_text.setColor(sf::Color::Black);
    sf::Text quit_text("Quit", menu_font, MENU_TEXT_SIZE);
    sf::FloatRect quit_text_rect = quit_text.getLocalBounds();
    quit_text.setPosition(sf::Vector2f(screen_width / 2 + offset_x + border_thickness + (button_width - options_text_rect.width) / 2,
                offset_y_top + 3 * border_thickness + new_game_button_height + options_button_height + (quit_button_height - quit_text_rect.height) / 2));
    quit_text.setColor(sf::Color::Black);


    sf::Text menu_title_text("Super cool title", menu_font, MENU_TITLE_TEXT_SIZE);
    sf::FloatRect menu_title_text_rect = menu_title_text.getLocalBounds();
    menu_title_text.setPosition((screen_width - menu_title_text_rect.width) / 2, (offset_y_top - menu_title_text_rect.height) / 2);
    menu_title_text.setColor(sf::Color::Black);

    bool menu_window_is_active = true;
    int button_selected = -1;//0 for new game, 1 for options, 2 for quit
    enum active_menu_area{NEW_GAME_BUTTON, OPTIONS_BUTTON, QUIT_BUTTON, THE_REST};//area containing mouse cursor
    active_menu_area current_area = THE_REST;


    bool is_fullscreen = true;

    while (menu_window_is_active) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        new_game_button.setFillColor(sf::Color::White);//reset colors of all buttons
        options_button.setFillColor(sf::Color::White);
        quit_game_button.setFillColor(sf::Color::White);
        button_selected = -1;//reset selected button variable

        auto mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (new_game_button.getGlobalBounds().contains(mouse_position)) {
            new_game_button.setFillColor(sf::Color::Yellow);
            button_selected = 0;
        } else if (options_button.getGlobalBounds().contains(mouse_position)) {
            options_button.setFillColor(sf::Color::Yellow);
            button_selected = 1;
        } else if (quit_game_button.getGlobalBounds().contains(mouse_position)) {
            quit_game_button.setFillColor(sf::Color::Yellow);
            button_selected = 2;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (button_selected == 0) {
                menu_window_is_active = false;
            } else if (button_selected == 1) {
                show_options_screen(window);
            } else if (button_selected == 2) {
                auto aa = quit_game_button.getGlobalBounds();
                window.close();
                menu_window_is_active = false;
            }
        }
        if (sf::Keyboard::isKeyPressed((sf::Keyboard::F2))) {
            window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Test!");
        }
        sf::Color background_color;
        if (button_selected == -1) {
            background_color = sf::Color(100,100,130);
        } else if (button_selected == 0) {
            background_color = sf::Color(130,100,100);
        } else if (button_selected == 1) {
            background_color = sf::Color(100,130,100);
        } else if (button_selected == 2) {
            background_color = sf::Color(100,100,100);
        }
        window.clear(background_color);
        window.draw(background_rect);
        window.draw(new_game_button);
        window.draw(options_button);
        window.draw(quit_game_button);
        window.draw(new_game_text);
        window.draw(options_text);
        window.draw(quit_text);
        window.draw(menu_title_text);
        window.display();
    }
}

#endif // MENU_H_
