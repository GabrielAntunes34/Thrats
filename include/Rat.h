#ifndef RAT_H
#define RAT_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

using namespace sf;
using namespace std;


class Rat {
    public:
        Rat(float x, float y, float radius);
        //mover o rato, retorna se colidiu com o player
        int move(                       
            Vector2f flow,                  //direção do flow field
            Vector2f separation,            //direção de separação
            Vector2u screenSize,            //tamanho da tela
            FloatRect playerBounds);        //bounding box do player

        void draw(RenderWindow &window);    //desenha o rato

        Vector2f getPosition();             //retorna a posição do rato
        int getRadius();                    //retorna o raio do rato

    private:
        float x, y, radius;                 //posição e raio do rato
        CircleShape shape;                  //forma do rato
        Texture ratTexture;                 //textura do rato
        int size;                           //tamanho do rato
};

#endif // RAT_H