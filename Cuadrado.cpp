#include "Cuadrado.h"

Cuadrado::Cuadrado(b2World& world, float x, float y, float size) {
    // SFML visual
    shape.setSize(sf::Vector2f(size, size));
    shape.setOrigin(size / 2, size / 2);
    shape.setFillColor(sf::Color::Blue);

    // Box2D cuerpo
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / SCALE, y / SCALE);
    body = world.CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox((size / 2) / SCALE, (size / 2) / SCALE);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.4f;

    body->CreateFixture(&fixtureDef);
}

void Cuadrado::draw(sf::RenderWindow& window) {
    b2Vec2 pos = body->GetPosition();
    shape.setPosition(pos.x * SCALE, pos.y * SCALE);
    window.draw(shape);
}

void Cuadrado::aplicarInput() {
    const float fuerza = 50.0f;
    b2Vec2 force(0, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        force.x -= fuerza;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        force.x += fuerza;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        force.y -= fuerza;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        force.y += fuerza;

    body->ApplyForceToCenter(force, true);
}

b2Body* Cuadrado::getBody() {
    return body;
}