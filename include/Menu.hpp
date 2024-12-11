#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "./TileMap.hpp"

using namespace std;

class Menu {
    private:
        sf::Font font;
        vector<sf::Text> menuText;
        int selectedIndex;
        sf::RenderWindow &window;
    
    public:
        Menu(sf::RenderWindow &window, const string &fontPath);
        int run(TileMap tileMap);
};

#endif 