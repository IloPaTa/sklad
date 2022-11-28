#include "AnimationManager.h"
#include<SFML/Graphics.hpp>

AnimationManager::AnimationManager() {

}

void AnimationManager::create(std::string type, sf::Texture& t, int x, int y, int w, int h, int count, double speed, int step) {
    Animation a;
    a.speed = speed;
    a.sprite.setTexture(t);
    a.sprite.setOrigin(0, h);
    for (int i = 0; i < count; i++)
    {
        a.frames.push_back(sf::IntRect(x + i * step, y, w, h));
        a.rev_frames.push_back(sf::IntRect(x + i * step + w, y, -w, h));
    }
    animList[type] = a;
    currentAnim = type;
}

void AnimationManager::drawAnim(sf::RenderWindow& window, int x, int y) {
    animList[currentAnim].sprite.setPosition(x, y);
    window.draw(animList[currentAnim].sprite);
}

void AnimationManager::set(std::string name) {
    currentAnim = name;
    animList[currentAnim].flip = 0;
}

void AnimationManager::flip(bool type) {
    animList[currentAnim].flip = type;
}

void AnimationManager::tick(double time) {
    animList[currentAnim].tick(time);
}

void AnimationManager::pause() {
    animList[currentAnim].isPlaying = false;
}

void AnimationManager::play() {
    animList[currentAnim].isPlaying = true;
}

sf::IntRect AnimationManager::getRect() {
    sf::IntRect ans = animList[currentAnim].frames[0];
    return ans;
}