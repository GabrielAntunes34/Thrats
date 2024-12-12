#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "./TileMap.hpp"

using namespace std;

// Classe que representa o menu do jogo, nele terá um botão para iniciar o jogo.
class Menu {
    private:
        sf::Font font;                  // Fonte do menu
        vector<sf::Text> menuText;      // Vetor de textos do menu
        sf::RenderWindow &window;       // Referência para a janela
    
    public:
        Menu(sf::RenderWindow &window, const string &fontPath); // Construtor
        int run(TileMap tileMap); // Executa o menu e retorna uma seleção
};

#endif 