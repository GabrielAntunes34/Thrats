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
        bool move(Vector2f flow);
        //desenhar o rato
        void draw(RenderWindow &window);

        Vector2f getPosition();
        int getRadius();

    private:
        float x, y, radius;
        CircleShape shape;
        Texture ratTexture;
};

#endif // RAT_H