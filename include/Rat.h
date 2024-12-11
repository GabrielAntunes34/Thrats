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
        //mover o rato
        int move(Vector2f flow, Vector2f separation, Vector2u screenSize, FloatRect playerBounds);
        //desenhar o rato
        void draw(RenderWindow &window);

        Vector2f getPosition();
        int getRadius();

    private:
        float x, y, radius;
        CircleShape shape;
        Texture ratTexture;
        int size;
};

#endif // RAT_H