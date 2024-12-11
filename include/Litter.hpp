#ifndef LITTER_H
#define LITTER_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "../include/Rat.h"
#include "../include/TileMap.hpp"

class Litter {
    private:
        vector<Rat> rats;
        int size;
        float gride_size;
        Vector2f spawn;
        TileMap &tileMap;

    public:
        Litter(Vector2f spawn, int size, TileMap &tileMap);
        void update(Vector2u screen_size);
        


        void draw(RenderWindow &window);
};

#endif