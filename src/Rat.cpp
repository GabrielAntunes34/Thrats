#include "../include/Rat.h"
#include <SFML/System/Vector2.hpp>

Rat::Rat(float x, float y, float radius) {
    this->x = x;
    this->y = y;
    this->radius = radius;

    shape.setRadius(radius);
    shape.setFillColor(Color::Red);
    shape.setPosition(x+0.5, y);

}

void Rat::draw(RenderWindow &window) {
    window.draw(shape);
}

void Rat::move() {
    // this->x += 0.1;
    this->y += 1;
    this->x += 1;
    shape.move(1, 1);
}

Vector2u Rat::getPosition() {
    radius = shape.getRadius();

    return Vector2u((unsigned int)x + 2.5* radius, (unsigned int)y + 2.5*radius);

}

int Rat::getRadius() {
    return this->shape.getRadius();
}