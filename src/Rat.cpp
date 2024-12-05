#include "../include/Rat.h"

Rat::Rat(float x, float y, float radius) {
    this->x = x;
    this->y = y;
    this->radius = radius;

    shape.setRadius(radius);
    shape.setFillColor(Color::Red);
    shape.setPosition(x, y);

}

void Rat::draw(RenderWindow &window) {
    window.draw(shape);
}

void Rat::move() {
    this->x += 0.1;
    shape.move(1, 0);
}