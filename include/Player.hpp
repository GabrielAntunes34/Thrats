#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../include/TileMap.hpp"

using namespace sf;
using namespace std;


#define MAX_SPEED 200.f
#define ACELERATION 400.f
#define DECELERATION 500.f

class Player {
    private:
        Vector2f position;
        Vector2f velocity;
        bool moving;
        bool alive;
        bool tangibility;
        Sprite sprite;
        int size;

    public:
        Player(Vector2f initPosition, Texture &texture, int tileSize);

        // Getters
        Vector2f getPosition();
        bool isAlive();
        bool isTangible();

        // Setters
        void setPosition(Vector2f position, Vector2u screenSize);
        void setLife(bool lifeState);
        void setTangibility(bool tangibility);

        // Mechanics
        void move(TileMap tileMap, Vector2u screenSize);
        void draw(RenderWindow &window);

};

#endif