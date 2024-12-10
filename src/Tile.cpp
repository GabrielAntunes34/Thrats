#include "../include/Tile.hpp"

// Tudo de que precisavamos no construtor já foi definido no .hpp!

// Getters
int Tile::getId() {
    return this->id;
}

bool Tile::isTangible() {
    return this->tangibility;
}

Sprite& Tile::getSprite() {
    return this->sprite;
}

int Tile::getCost() {
    return this->cost;
}

float Tile::getDistance() {
    return this->distance;
}

Vector2f Tile::getFlowDirection() {
    return this->flowDirection;
}


// Setters
void Tile::setId(int id) {
    this->id = id;
}

void Tile::setTaniblity(bool tangibility) {
    this->tangibility = tangibility;
}

void Tile::setSprite(Texture& texture) {
    this->sprite.setTexture(texture);
}

void Tile::setCost(float cost) {
    this->cost = cost;
}

void Tile::setDistance(float distance) {
    this->distance = distance;
}

void Tile::setFlowDirection(Vector2f flowDirection) {
    this->flowDirection = flowDirection;
}
