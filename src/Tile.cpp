#include "../include/Tile.hpp"

// Tudo de que precisavamos no construtor já foi definido no .hpp!

// Getters
int Tile::getId() {
    return this->id;
}

bool Tile::isTangible() {
    return this->tangibility;
}

Sprite Tile::getSprite() {
    return this->sprite;
}


// Setters
void Tile::setId(int id) {
    this->id = id;
}

void Tile::setTaniblity(bool tangibility) {
    this->tangibility = tangibility;
}

void Tile::setSprite(Texture texture) {
    this->sprite.setTexture(texture);
}
