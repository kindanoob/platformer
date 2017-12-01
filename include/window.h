#ifndef WINDOW_H_
#define WINDOW_H_


#include <SFML/Graphics.hpp>

class My_window: public sf::RenderWindow {
public:
    My_window(sf::VideoMode mode, const sf::String &title, sf::Uint32 style = sf::Style::Default, sf::ContextSettings settings = sf::ContextSettings()):
                  sf::RenderWindow(mode, title, style, settings) {
        is_fullscreen = false;
    };
    bool get_is_fullscreen();
private:
    bool is_fullscreen = false;
};




#endif // WINDOW_H_
