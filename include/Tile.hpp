#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
using namespace sf;

#define PLAYER 0
#define ENEMY 3
#define GROUND 1
#define OBSTACLE 4
#define GOAL 2

class Tile {
    private:
        int id;
        bool tangibility;
        Sprite sprite;

        float cost; //custo deste tile
        float distance; //distancia do tile destino (Integration field)
        Vector2f flowDirection; //Diretaçao do flow field

    public:   
        // Getters
        int getId();
        bool isTangible();
        Sprite& getSprite();
        int getCost();
        float getDistance();
        Vector2f getFlowDirection();


        // Setters
        void setTaniblity(bool tangibility);
        void setId(int id);
        void setSprite(Texture &texture, float correcao);

        void setCost(float cost);
        void setDistance(float distance);
        void setFlowDirection(Vector2f flowDirection);
        // Mechanics
        // CalculatePath???
};

#endif