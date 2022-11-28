#pragma once

#include <SFML/Graphics.hpp>


class Animation {
public:
    std::vector<sf::IntRect> frames, rev_frames;
    double currentFrame, speed;
    bool flip, isPlaying;
    sf::Sprite sprite;
    Animation(){
        currentFrame = 0;
        isPlaying = true;
        flip = false;
    }
    Animation(sf::Texture& t, int x, int y, int w, int h, int count, double Speed, int step) {
        speed = Speed;
        sprite.setTexture(t);

        currentFrame = 0;
        isPlaying = true;
        flip = false;

        for (int i = 0; i < count; ++i) {
            frames.push_back(sf::IntRect(x + i * step, y, w, h));
            rev_frames.push_back(sf::IntRect(x + i * step + w, y, -w, h));
        }
    }

    void tick(double time);
};

