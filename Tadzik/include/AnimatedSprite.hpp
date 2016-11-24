#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

struct AnimationFrame{
    sf::Texture* texture;
    float duration;
    AnimationFrame(sf::Texture* t, float d)
    :duration(d)  //[ms]
    {
        texture = t;
    }
};

class Animation
{
public:
    std::string getName()           {return name;}
    void setName(std::string _name) {name = _name;}
    void addFrame(AnimationFrame f) {vecFrames.push_back(f);}
    std::vector<AnimationFrame> vecFrames;                   //nie chce mi sie calego vectora pisac

protected:
    std::string name;
};

class AnimatedSprite
{
public:
    void setAnimation(Animation* a){
        currentAnimation = a;
        actFrame=0;

        if(currentAnimation->vecFrames.size() == 0){
            std::cout << "dafuq? AnimatedSprite::setAnimation()\n";
        }
        sprite.setTexture(*currentAnimation->vecFrames[0].texture, true);
    }

    void update(float delta){
        currTime += delta;
        if(currTime > currentAnimation->vecFrames[actFrame].duration){
            actFrame=(actFrame+1)%currentAnimation->vecFrames.size();
            sprite.setTexture(*currentAnimation->vecFrames[actFrame].texture);
            currTime=0;
        }
    }

    void move(double x, double y) {
        sprite.move(x, y);
    }
    Animation* getAnimation() {
        return currentAnimation;
    }
    sf::Sprite sprite;
    Animation* currentAnimation;

protected:
    float currTime=0;
    int actFrame=0;
};


#endif // ANIMATED_SPRITE_H