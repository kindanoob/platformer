#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
	std::vector<sf::IntRect> frames;
	std::vector<sf::IntRect> frames_flip;
	double current_frame;
	double speed;
	bool loop = false;
	bool flip = false;
	bool is_playing;
	sf::Sprite sprite;
	Animation();
	void tick(double time);
};

Animation::Animation() {
    current_frame = 0;
    is_playing = true;
    flip = false;
    loop = true;
}

void Animation::tick(double time) {
    if (!is_playing) {
        return;
    }
    current_frame += speed * time;
    if (current_frame >= frames.size()) {
        current_frame -= frames.size();
        if (!loop) {
            is_playing = false;
            return;
        }
    }
    int current_frame_int = static_cast<int>(current_frame);
    sprite.setTextureRect(frames[current_frame_int]);
    if (flip) {
        sprite.setTextureRect(frames_flip[current_frame_int]);
    }
}

#endif // ANIMATION_H_
