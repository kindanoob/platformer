#ifndef ANIMATION_MANAGER_H_
#define ANIMATION_MANAGER_H_

#include "animation.h"
#include<map>

class AnimationManager
{

public:
    std::string current_animation;
	std::map<std::string, Animation> animation_map;

	AnimationManager() {};

	~AnimationManager() {
        animation_map.clear();
	}
	AnimationManager& operator=(const AnimationManager &other);
	void create(const std::string &name, const sf::Texture &texture,
             int x, int y, int w, int h, int frame_count, double speed, int step = 0, bool loop = true);
    void set_animation(std::string name);
    void draw(sf::RenderWindow &window, int x = 0, int y = 0);
    void flip(bool b = true);
    void tick(double time);
    void pause();
    void play();
    void play(std::string name);
    bool is_playing();
    double get_h();
    double get_w();
    Animation get_current_animation();
};


AnimationManager& AnimationManager::operator=(const AnimationManager& other) {
    if (&other == this) {
        return *this;
    }
    current_animation = other.current_animation;
    animation_map = other.animation_map;
    return *this;
}

void AnimationManager::create(const std::string &name, const sf::Texture &texture,
                           int x, int y, int w, int h, int frame_count, double speed, int step, bool loop) {
    Animation a;
    a.speed = speed;
    a.loop = loop;
    a.sprite.setTexture(texture);

    for (int i = 0; i < frame_count; ++i) {
        a.frames.push_back(sf::IntRect(x + i * step, y, w, h));
        a.frames_flip.push_back(sf::IntRect(x + i * step + w, y, -w, h));
    }
    animation_map[name] = a;
    current_animation = name;
}

void AnimationManager::set_animation(std::string name) {
    current_animation = name;
    animation_map[current_animation].flip = 0;
}

void AnimationManager::draw(sf::RenderWindow &window, int x, int y) {
    animation_map[current_animation].sprite.setPosition(x,y);
    window.draw(animation_map[current_animation].sprite);
}

void AnimationManager::flip(bool b) {
    animation_map[current_animation].flip = b;
}


void AnimationManager::tick(double time) {
    animation_map[current_animation].tick(time);
}

void AnimationManager::pause() {
    animation_map[current_animation].is_playing = false;
}

void AnimationManager::play() {
    animation_map[current_animation].is_playing = true;
}

void AnimationManager::play(std::string name) {
    animation_map[name].is_playing = true;
}


bool AnimationManager::is_playing() {
    return animation_map[current_animation].is_playing;
}

double AnimationManager::get_h() {
    return animation_map[current_animation].frames[0].height;
}


double AnimationManager::get_w() {
    return animation_map[current_animation].frames[0].width;
}


Animation AnimationManager::get_current_animation() {
    return animation_map[current_animation];
}

#endif // ANIMATION_MANAGER_H_
