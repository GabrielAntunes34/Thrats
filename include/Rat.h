#ifndef RAT_H
#define RAT_H

#include <SFML/Graphics.hpp>
using namespace sf;


class Rat {
    public:
        Rat(float x, float y, float radius);
        //mover o rato
        void move();
        //desenhar o rato
        void draw(RenderWindow &window);

    private:
        float x, y, radius;
        CircleShape shape;
};

#endif // RAT_H