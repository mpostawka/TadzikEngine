#ifndef RPG_HPP
#define RPG_HPP

#include "Scene.hpp"
#include "AnimatedSprite.hpp"
#include "Collision.hpp"
#include "Utils.hpp"

#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>

class RPG: public Scene{
public:
    RPG(std::string _name, SceneManager* mgr, sf::RenderWindow* w)
    :Scene(_name, mgr, w)
    {}

    void loadMap() {
        for (int i=0; i<mapa.getSize().y; i++) {
            for (int j=0; j<mapa.getSize().x; j++) {
                if (mapa.getPixel(i, j)==sf::Color(0, 0, 0)) {

                }
            }
        }
    }

    virtual void onSceneLoadToMemory() {
        if (!font.loadFromFile("files/Carnevalee_Freakshow.ttf")) {
            std::cout << "cannot load font\n";
        }
        texTadeusz.loadFromFile("files/textures/universal/playerStand.png");
        spTadeusz.setTexture(texTadeusz);
        spTadeusz.setScale(5, 5);
        mapa.loadFromFile("files/maps/rpg/mapa1.png");
    }

    virtual void onSceneActivate() {

    }

    void deliverEvent(sf::Event& event){


    }

    virtual void draw(double deltaTime) {
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
            spTadeusz.move(-5, 0);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
            spTadeusz.move(0, -5);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
            spTadeusz.move(0, 5);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
            spTadeusz.move(5, 0);
        }
        window->clear(sf::Color());
        window->draw(spTadeusz);
    }

protected:
    sf::Font font;
    sf::Texture texTadeusz;
    sf::Sprite spTadeusz;
    sf::Image mapa;

};
#endif //RPG