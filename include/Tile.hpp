#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
using namespace sf;

//ID dos tiles =================================
#define PLAYER 0     
#define GROUND 1
#define GOAL 2
#define ENEMY 3
#define OBSTACLE 4

class Tile {
    private:
        int id;             //ID do tile
        bool tangibility;   //Se o tile é tangível
        Sprite sprite;      //Sprite do tile

        float cost;                 //custo deste tile
        float distance;             //distancia do tile destino (Integration field)
        Vector2f flowDirection;     //Diretaçao do flow field

    public:   
        // Getters
        int getId();                 //retorna o id do tile
        bool isTangible();           //retorna se o tile é tangível
        Sprite& getSprite();         //retorna o sprite do tile
        int getCost();               //retorna o custo do tile
        float getDistance();         //retorna a distancia do tile destino
        Vector2f getFlowDirection(); //retorna a direção do flow field


        // Setters
        void setTaniblity(bool tangibility);      //
        void setId(int id);
        void setSprite(Texture &texture, float correcao);

        void setCost(float cost);
        void setDistance(float distance);
        void setFlowDirection(Vector2f flowDirection);
        // Mechanics
        // CalculatePath???
};

#endif