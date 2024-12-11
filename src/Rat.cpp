#include "../include/Rat.h"
#include <cmath>
#include <SFML/System/Vector2.hpp>


Rat::Rat(float x, float y, float radius) {
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->size = 16;

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

bool Rat::move(sf::Vector2f flow, sf::Vector2f separation, Vector2u screenSize) {
    if (std::fabs(flow.x) < 0.0001f && std::fabs(flow.y) < 0.0001f) {
        return false;
    }

    // Combina o vetor de fluxo com o vetor de separação
    sf::Vector2f combined = flow + separation;
    pair<float, float> newPosition = {this->x + combined.x, this->y + combined.y};

    if(!(newPosition.first < 0 || newPosition.first >= screenSize.x - this->size))
        this->x = newPosition.first;
    else
        combined.x = 0;
    if(!(newPosition.second < 0 || newPosition.second >= screenSize.y - this->size))
        this->y = newPosition.second;
    else
        combined.y = 0;
    shape.move(combined.x, combined.y);
    float angle = std::atan2(combined.y, combined.x) * 180 / M_PI;
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