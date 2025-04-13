#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#define SCALE 100.0f

class Cuadrado {
public:
    Cuadrado(b2World& world, float x, float y, float size);

    void draw(sf::RenderWindow& window);
    void aplicarInput(); // aplicar fuerza según teclas
    b2Body* getBody();

private:
    b2Body* body;
    sf::RectangleShape shape;
};
