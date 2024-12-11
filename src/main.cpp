#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <vector>

#include "../include/TileMap.hpp"
#include "../include/Rat.h"
#include "../include/Menu.hpp"

using namespace sf;
using namespace std;

int main()
{
    VideoMode desktop = VideoMode::getDesktopMode(); // Tamanho da tela

    RenderWindow window(sf::VideoMode(desktop), "Threads - The Game!");
    window.setFramerateLimit(60); // Limita a janela a 60 FPS
    CircleShape shape(100.f); // Cria um círculo de raio 100
    shape.setFillColor(sf::Color::Green); // Preenche o círculo de verde

    
    TileMap tileMap(window.getSize());

    // Carrega o mapa
    tileMap.loadMap("assets/testGround.csv");

    // Configuracoes menu


    // Definindo o objetivo:do que o objetivo é o jogador, cuja posicao inicial está em initPlayerPosition.
    // Suponha que o objetivo é o jogador
    // precisamos transformar em cordenadas de tile

    //SE QUISERMOS VER A POSICAO DO PLAYER:

    // Vector2u PlayerTilePos = Vector2u(tileMap.pixelsToTileGrid(tileMap.getInitPlayerPosition()).first,
    //                                   tileMap.pixelsToTileGrid(tileMap.getInitPlayerPosition()).second);

    // tileMap.generateIntegrationField(PlayerTilePos);
    // tileMap.generateFlowField();    

    Rat rat(20, 100, 10);

    //Contador para decidir quando recalcular o flow field (fazer todo frame é custoso)
    int frameCounter = 0;
    int framesToRecalculate = 1;

    Vector2u ratTilePos = Vector2u(5, 5);

    int i = 0;

    Menu menu(window, "assets/Pixeled.ttf");
    // Mostrar o menu e obter a seleção
    int menuSelection = menu.run(tileMap);

    while (window.isOpen())
    {
        if (menuSelection == 0) {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            tileMap.generateIntegrationField(ratTilePos);
            tileMap.generateFlowField();

            // ver o tile q o rato tá
            auto [x, y] = rat.getPosition();
            auto [a, b] = tileMap.pixelsToTileGrid(Vector2f(x, y));
            Tile rat_tile = tileMap.getTile(b, a);
            // pegar o vetor de mov. desse tile e atualizar a pos do rato
            Vector2f vector = rat_tile.getFlowDirection();
            rat.move(vector);
            
            window.clear();
            
            tileMap.draw(window);
            rat.draw(window);
            tileMap.drawFlowField(window);

            window.display();
        }
        
    }
        
        

    return 0;
}
