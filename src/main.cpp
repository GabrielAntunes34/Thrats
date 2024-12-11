#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <string>
#include <vector>

#include "../include/TileMap.hpp"
#include "../include/Rat.h"
#include "../include/Player.hpp"


using namespace sf;
using namespace std;

int main()
{
    VideoMode desktop = VideoMode::getDesktopMode(); // Tamanho da tela

    int maps_available = 2; //MAPAS DISPONIVEIS
    int current_map = 0; //MAPA ATUAL

    RenderWindow window(sf::VideoMode(desktop), "Threads - The Game!");
    window.setFramerateLimit(60); // Limita a janela a 60 FPS
    CircleShape shape(100.f); // Cria um círculo de raio 100
    shape.setFillColor(sf::Color::Green); // Preenche o círculo de verde

    
    TileMap tileMap(window.getSize());

    // Carrega o mapa
    tileMap.loadMap("assets/map"+to_string(current_map)+".csv");

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
    

    // Shape do maluco
    Texture tex;
    if(!tex.loadFromFile("assets/charac.png")) {
        cerr << "Falha ao carregar o shape do maluco" << endl;
        return -1;
    }

    Player player(Vector2f(0.f, 0.f), tex, tileMap.getTileSize());
    player.setPosition(tileMap.getInitPlayerPosition(), window.getSize());


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        
        // ver o tile q o rato tá
        auto [x, y] = rat.getPosition();
        auto [a, b] = tileMap.pixelsToTileGrid(Vector2f(x, y));
        Tile rat_tile = tileMap.getTile(b, a);

        tileMap.generateIntegrationField(ratTilePos);
        tileMap.generateFlowField();

        // pegar o vetor de mov. desse tile e atualizar a pos do rato
        Vector2f vector = rat_tile.getFlowDirection();
        rat.move(vector);
        player.move(tileMap,window.getSize());


        window.clear();

        tileMap.draw(window);
        rat.draw(window);
        tileMap.drawFlowField(window);

        //verifica se o player chegou no objetivo
        if(tileMap.verifyPosition(player.getPosition()) == GOAL){
            cout << "Player chegou no objetivo" << endl;
            current_map = (current_map + 1) % maps_available;
            tileMap.loadMap("assets/map"+to_string(current_map)+".csv");
            player.setPosition(tileMap.getInitPlayerPosition(), window.getSize());
        }

        window.display();
    }

    return 0;
}
