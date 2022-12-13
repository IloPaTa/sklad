#include "Animation.h"
#include <SFML/Graphics.hpp>

//void Animation::tick(double time) {
//    if (!isPlaying)
//        return;
//    
//    currentFrame += speed * time;
//    if (currentFrame >= frames.size() || currentFrame < 0) {
//        currentFrame = 0;
//    }
//
//    int i = currentFrame;
//    sprite.setTextureRect(frames[i]);
//    if(flip)
//        sprite.setTextureRect(rev_frames[i]);
//}