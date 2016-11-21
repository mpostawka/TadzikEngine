#ifndef MARIO_HPP
#define MARIO_HPP

#include "Scene.hpp"
#include "AnimatedSprite.hpp"
#include "Collision.hpp"
#include "Utils.hpp"

#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>

class MARIO: public Scene{
public:
    MARIO(std::string _name, SceneManager* mgr, sf::RenderWindow* w)
    :Scene(_name, mgr, w)
    {}
    virtual void onSceneLoadToMemory() {
        texBackground.loadFromFile("files/textures/mario/background.png");
        Background.setTexture(texBackground);
        Background.setScale(double(window->getSize().x)/double(Background.getTextureRect().width),
                            double(window->getSize().y)/double(Background.getTextureRect().height));

        texPlayerStand.loadFromFile("files/textures/mario/playerStand.png"), TadzikStand.addFrame(AnimationFrame(&texPlayerStand, 150));
        spTadzik.setAnimation(&TadzikStand);
        spTadzik.sprite.setOrigin(sf::Vector2f(spTadzik.sprite.getTextureRect().width/2, spTadzik.sprite.getTextureRect().height));
        spTadzik.sprite.setScale(2, 2);

        texFloorTile.loadFromFile("files/textures/mario/floor1.png");
        mapa.loadFromFile("files/maps/mario/map1.png");
        loadMap();
    }

    virtual void onSceneActivate() {

    }

    void deliverEvent(sf::Event& event){
        if (event.type == sf::Event::MouseButtonPressed) {

        }
    }

    void loadMap() {
        for (int i=0; i<mapa.getSize().x; i++) {
            for (int j=0; j<mapa.getSize().y; j++) {
                if (mapa.getPixel(i, j)==sf::Color::Black || mapa.getPixel(i, j)==sf::Color::White) {
                    sf::Sprite tmp;
                    tmp.setTexture(texFloorTile);
                    tmp.setPosition(i*tmp.getGlobalBounds().width, j*tmp.getGlobalBounds().height);
                    floor.push_back(tmp);
                }
            }
        }
    }
    void gameOver() {
    }

    void jump() {
        speedY=13;
        isStanding = false;
        isJumping = true;
    }
    void flip() {
        spTadzik.sprite.setScale(-spTadzik.sprite.getScale().x, spTadzik.sprite.getScale().y);
    }

    bool checkForStanding(sf::Sprite s1) {
            if (Collision::BoundingBoxTest(s1, spTadzik.sprite)) {
                standingHeight = s1.getGlobalBounds().top;
            }
        }


    virtual void draw(double deltaTime) {
        prevTop = spTadzik.sprite.getGlobalBounds().top;
        prevBot = spTadzik.sprite.getGlobalBounds().top+spTadzik.sprite.getGlobalBounds().height;
        prevLeft = spTadzik.sprite.getGlobalBounds().left;
        prevRight = spTadzik.sprite.getGlobalBounds().left+spTadzik.sprite.getGlobalBounds().width;
        prevX = spTadzik.sprite.getPosition().x;
        prevY = spTadzik.sprite.getPosition().y;


        spTadzik.move(speedX, 0);
        speedY-=gravity;
        spTadzik.sprite.move(0, -speedY);


        for (auto s:floor) {
            if (Collision::BoundingBoxTest(spTadzik.sprite, s)) {

                if (s.getGlobalBounds().top+s.getGlobalBounds().height<prevTop) {
                    speedY = 0;
                    spTadzik.sprite.setPosition(spTadzik.sprite.getPosition().x,
                                                s.getGlobalBounds().top+s.getGlobalBounds().height+spTadzik.sprite.getGlobalBounds().height);
                }
                if (s.getGlobalBounds().top>=prevBot) {
                    isStanding = true;
                    touched = true;
                    //prevY = s.getGlobalBounds().top;
                    spTadzik.sprite.setPosition(spTadzik.sprite.getPosition().x, s.getGlobalBounds().top);
                    speedY = 0;
                }
                else if (s.getGlobalBounds().left>prevRight) {
                    spTadzik.sprite.setPosition(prevX, spTadzik.sprite.getPosition().y);
                    speedX = 0;
                }
                else if (s.getGlobalBounds().left+s.getGlobalBounds().width<prevLeft+1) {
                    spTadzik.sprite.setPosition(prevX, spTadzik.sprite.getPosition().y);
                    speedX = 0;
                }
            }
        }
        touched = false;
        if (isJumping) {
            if (speedY>0) isJumping = false;
        }
        speedX*=0.9;
        //input z klawiatury
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && -speedX<maxSpeed) {
            speedX-=1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && speedX<maxSpeed) {
            speedX+=1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && isStanding) {
            jump();
        }

        //rysowanie
        window->clear();
        window->draw(Background);
        for (auto a:floor) {
            window->draw(a);
        }
        window->draw(spTadzik.sprite);
    }

protected:
    sf::Texture texBackground;
    sf::Texture texPlayerStand;
    sf::Texture texFloorTile;

    sf::Image mapa;


    Animation TadzikStand;
    AnimatedSprite spTadzik;

    sf::Sprite Background;
    sf::Sprite FloorTile;

    std::vector <sf::Sprite> floor;

    double speedX = 0, speedY=0;
    double maxSpeed = 10;
    double gravity = 0.5;
    double standingHeight = 0;

    double prevLeft, prevRight, prevTop, prevBot, prevX, prevY;

    int onTile = 0;

    bool isStanding = false;
    bool isJumping = false;
    bool touched = false;
};
#endif //mario