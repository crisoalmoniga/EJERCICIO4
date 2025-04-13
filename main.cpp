#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Cuadrado.h"

#define SCALE 100.0f

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ejercicio 4 - Cuadrado con input");
    window.setFramerateLimit(60);

    b2Vec2 gravity(0.f, 0.f); // sin gravedad
    b2World world(gravity);

    // Crear el cuadrado
    Cuadrado cuadrito(world, 400, 300, 40); // posición x, y y tamaño

    // Crear bordes del mundo
    b2BodyDef groundDef;
    groundDef.position.Set(0, 0);
    b2Body* ground = world.CreateBody(&groundDef);

    b2EdgeShape edge;
    b2FixtureDef fixture;
    fixture.shape = &edge;

    // Piso
    edge.SetTwoSided(b2Vec2(0, 6), b2Vec2(8, 6));
    ground->CreateFixture(&fixture);
    // Techo
    edge.SetTwoSided(b2Vec2(0, 0), b2Vec2(8, 0));
    ground->CreateFixture(&fixture);
    // Izquierda
    edge.SetTwoSided(b2Vec2(0, 0), b2Vec2(0, 6));
    ground->CreateFixture(&fixture);
    // Derecha
    edge.SetTwoSided(b2Vec2(8, 0), b2Vec2(8, 6));
    ground->CreateFixture(&fixture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Aplicar input
        cuadrito.aplicarInput();

        // Simular física
        world.Step(1.f / 60.f, 8, 3);

        // Dibujar
        window.clear(sf::Color::Black);
        cuadrito.draw(window);
        window.display();
    }

    return 0;
}