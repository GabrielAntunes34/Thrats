#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
using namespace sf;

#define PLAYER 0
#define ENEMY 1
#define GROUND 2
#define OBSTACLE 3

class Tile {
    private:
        int id;
        bool tangibility;
        Sprite sprite;

    public:   
        // Getters
        int getId();
        bool isTangible();
        Sprite& getSprite();

        // Setters
        void setTaniblity(bool tangibility);
        void setId(int id);
        void setSprite(Texture &texture);

        // Mechanics
        // CalculatePath???
};

#endif