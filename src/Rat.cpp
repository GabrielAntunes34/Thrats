#include "../include/Rat.h"
#include <cmath>
#include <SFML/System/Vector2.hpp>


Rat::Rat(float x, float y, float radius) {
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->size = 16;

    shape.setRadius(radius);
    // Ajustando a origem para o centro
    shape.setOrigin(radius, radius);
    // Agora (x,y) é o centro do shape
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

    // Nova posição lógica do centro do rato
    float newX = this->x + combined.x;
    float newY = this->y + combined.y;

    // Verifica se não sai da tela, considerando half-size
    float halfSize = this->size / 2.0f;
    if (!(newX - halfSize < 0 || newX + halfSize >= screenSize.x))
        this->x = newX;
    else
        combined.x = 0;
    if (!(newY - halfSize < 0 || newY + halfSize >= screenSize.y))
        this->y = newY;
    else
        combined.y = 0;

    // Atualiza a posição do shape (já centrada)
    shape.setPosition(this->x, this->y);

    float angle = std::atan2(combined.y, combined.x) * 180 / M_PI;
    shape.setRotation(angle);
    return true;
}

Vector2f Rat::getPosition() {
    // Agora, como definimos a origem do shape no centro,
    // (x, y) já é o centro do rato
    return Vector2f(x, y);
}

int Rat::getRadius() {
    return this->shape.getRadius();
}