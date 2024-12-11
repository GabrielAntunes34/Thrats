#include "../include/Rat.h"
#include <cmath>
#include <SFML/System/Vector2.hpp>


Rat::Rat(float x, float y, float radius) {
    this->x = x;
    this->y = y;
    this->radius = radius;

    shape.setRadius(radius);
    shape.setPosition(x, y);


    // textura do objetivo
    if(!this->ratTexture.loadFromFile("assets/ratinho.png")) {
        cerr << "Erro ao carregar a textura do objetivo" << endl;
    }    
    shape.setTexture(&ratTexture);
}

void Rat::draw(RenderWindow &window) {
    window.draw(shape);
}

bool Rat::move(Vector2f flow) {
    if (fabs(flow.x) < 0.0001f && fabs(flow.y) < 0.0001f) {
        return false;
    }

    this->y += flow.y;
    this->x += flow.x;
    shape.move(flow.x, flow.y);
    float angle = atan2(flow.y, flow.x) * 180 / M_PI;
    shape.setRotation(angle);
    return true;
}

Vector2f Rat::getPosition() {
    radius = shape.getRadius();

    return Vector2f(x + 2.5* radius, y + 2.5*radius);

}

int Rat::getRadius() {
    return this->shape.getRadius();
}