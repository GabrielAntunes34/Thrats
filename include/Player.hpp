#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "../include/TileMap.hpp"

using namespace sf;
using namespace std;


#define MAX_VELOCITY 350.f
#define ACELERATION 220.f
#define DECELERATION 325.f

class Player {
    private:
        Vector2f position;          // Posição atual do jogador
        Vector2f currentDirection;  // Guarda a direção do deslocamento atá a velocidade zerar
        float velocity;             // Armazena o vetor velocidade do movimento
        bool moving;                // Verifica se ele está se movmento
        bool alive;                 // Verifica se ele está vivo
        bool tangibility;           // Verifica se ele é tangível
        Sprite sprite;
        int size;

        float offsetX;              // Offset para ajustar a posição do sprite
        float offsetY;              // Offset para ajustar a posição do sprite

    public:
        Player(Vector2f initPosition, Texture &texture, int tileSize);

        // Getters
        Vector2f getPosition();
        FloatRect getBounds();
        bool isAlive();
        bool isTangible();

        // Setters
        void setPosition(Vector2f position, Vector2u screenSize);
        void setLife(bool lifeState);
        void setTangibility(bool tangibility);

        // Mechanics
        void move(Time deltaTime, TileMap tileMap, Vector2u screenSize);
        void draw(RenderWindow &window);

};

#endif