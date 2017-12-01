#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "map.h"
#include "animation_manager.h"

const double TIME_ADJUSTMENT = 800;//in milliseconds


//directions of collision checks
enum DIRECTION {
    HORIZONTAL, 
    VERTICAL
};


class Entity {
public:
    double x;//coordinate equal to rect.left
    double y;//coordinate equal to rect.top
    double dx;
    double dy;
    double w;
    double h;
    double dx_prev;
    bool is_alive;
    double timer;
    double timer_end;
    std::string name;
    int health;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::FloatRect rect;
    double current_frame;
    int damage;
    double dead_duration;
    AnimationManager animation_manager;
    Entity(const sf::Texture &texture, const std::string &m_name, int m_x, int m_y, int m_w, int m_h, int row, int col);
    virtual void update(double time, GameMap &game_map, double offset_x, double offset_y) = 0;
    virtual void set_animations() = 0;
    void draw(sf::RenderWindow &window, int x, int y);
    sf::FloatRect get_rect() const;
    double get_x() const;
    double get_y() const;
    void set_x(double new_x);
    void set_y(double new_y);
    double get_dx() const;
    double get_dy() const;
    void set_dx(double new_dx);
    void set_dy(double new_dy);
    double get_w() const;
    double get_h() const;
    void set_w(double new_w);
    void set_h(double new_h);
    void set_timer(double t);
    double get_timer();
    void set_is_alive(bool alive);
    bool get_is_alive();
    void set_damage(int l_damage);
    int get_damage();
    double get_dx_prev();
    void set_dx_prev(double l_dx_prev);
    void set_texture(const sf::Texture &l_texture);
};

Entity::Entity(const sf::Texture &m_texture, const std::string &m_name, 
    int m_x, int m_y, int m_w, int m_h, int row, int col) {
    //row and col are used to extract
    //the tile (from the tileset ) that corresponds to the initial position of entity
    x = m_x;
    y = m_y;
    w = m_w;
    h = m_h;
    current_frame = col;
    set_texture(m_texture);
    sprite.setTexture(m_texture);
    sprite.setTextureRect(sf::IntRect(col * w, row * h, w, h));
    rect = sf::FloatRect(x, y, w, h);
    dx = 0;
    dy = 0;
    dx_prev = 1;//by default character's last move in x-axis was in the left direction
    is_alive = true;
    timer = 0;
    timer_end = 0;
    name = m_name;
}

void Entity::draw(sf::RenderWindow &window, int offset_x, int offset_y) {
    animation_manager.draw(window, get_x() - offset_x, get_y() - offset_y);
    //sprite.setPosition(x, y);
    //window.draw(sprite);
}

sf::FloatRect Entity::get_rect() const {
    return sf::FloatRect(get_x(), get_y(), get_w(), get_h());
}

double Entity::get_x() const {
    return rect.left;
}

double Entity::get_y() const {
    return rect.top;
}

void Entity::set_x(double new_x) {
    rect.left = new_x;
}

void Entity::set_y(double new_y) {
    rect.top = new_y;
}

double Entity::get_dx() const {
    return dx;
}

double Entity::get_dy() const {
    return dy;
}

void Entity::set_dx(double new_dx) {
    dx = new_dx;
}

void Entity::set_dy(double new_dy) {
    dy = new_dy;
}

double Entity::get_w() const {
    return w;
}

double Entity::get_h() const {
    return h;
}

void Entity::set_w(double new_w) {
    w = new_w;
}

void Entity::set_h(double new_h) {
    h = new_h;
}

void Entity::set_timer(double t) {
    timer = t;
}

double Entity::get_timer() {
    return timer;
}

void Entity::set_is_alive(bool alive) {
    is_alive = alive;
}

bool Entity::get_is_alive() {
    return is_alive;
}

void Entity::set_damage(int l_damage) {
    damage = l_damage;
}

int Entity::get_damage() {
    return damage;
}

void Entity::set_dx_prev(double l_dx_prev) {
    dx_prev = l_dx_prev;
}

double Entity::get_dx_prev() {
    return dx_prev;
}

void Entity::set_texture(const sf::Texture &l_texture) {
    texture = l_texture;
}

#endif // ENTITY_H_

