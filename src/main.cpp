#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <vector>

#include "../include/TileMap.hpp"
#include "../include/Rat.h"

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

    // Definindo o objetivo:do que o objetivo é o jogador, cuja posicao inicial está em initPlayerPosition.
    // Suponha que o objetivo é o jogador
    // precisamos transformar em cordenadas de tile

    Vector2u PlayerTilePos = Vector2u(tileMap.pixelsToTileGrid(tileMap.getInitPlayerPosition()).first,
                                      tileMap.pixelsToTileGrid(tileMap.getInitPlayerPosition()).second);

    tileMap.generateIntegrationField(PlayerTilePos);
    tileMap.generateFlowField();    


    Rat rat(100, 100, 10);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        rat.move();

        window.clear();

        rat.draw(window);
        tileMap.draw(window); //alterado para desenhar o flow field 
        
        window.display();
    }

    return 0;
}
