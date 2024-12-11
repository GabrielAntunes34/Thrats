#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <ostream>
#include <string>
#include <vector>

#include "../include/TileMap.hpp"
#include "../include/Rat.h"
#include "../include/Menu.hpp"
#include "../include/Player.hpp"
#include "../include/Litter.hpp"


using namespace sf;
using namespace std;

int main()
{
    VideoMode desktop = VideoMode::getDesktopMode(); // Tamanho da tela
    Clock clock;                                     // clock global do jogo
    // ===============
    // MAPAS
    // ===============

    int maps_available = 3; //MAPAS DISPONIVEIS
    int current_map = 1; //MAPA ATUAL


    // ===============
    // JANELA
    // ===============

    RenderWindow window(sf::VideoMode(desktop), "Threads - The Game!");
    window.setFramerateLimit(60); // Limita a janela a 60 FPS

    // ===============
    // TILEMAP
    // ===============

    TileMap tileMap(window.getSize());
    // Carrega o mapa
    tileMap.loadMap("assets/map"+to_string(current_map)+".csv");

    // =================
    // Seres vivos
    // =================

    // Shape do Player
    Texture tex;
    if(!tex.loadFromFile("assets/bruno_antunes_barbosa.png")) {
        cerr << "Falha ao carregar o shape do maluco" << endl;
        return -1;
    }

    // cria o player
    Player player(Vector2f(0.f, 0.f), tex, tileMap.getTileSize());
    player.setPosition(tileMap.getInitPlayerPosition(), window.getSize());

    
    Menu menu(window, "assets/Pixeled.ttf");
    // Mostrar o menu e obter a seleção
    
    int menuSelection = menu.run(tileMap);

    // Ninhada
    
    Litter litter(tileMap.getEnemiesPositions()[0], 500, tileMap);
    Litter litter2(tileMap.getEnemiesPositions()[1], 500, tileMap);

    while (window.isOpen())
    {
        if (menuSelection == 0) {

            //eventos
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            // Fazendo o flow field
            Vector2f goal = player.getPosition();
            //converter goal para pixelsToTileGrid
            Vector2f goalTilePos = Vector2f(tileMap.pixelsToTileGrid(goal).first,
                                            tileMap.pixelsToTileGrid(goal).second);

            tileMap.generateIntegrationField(goalTilePos);
            tileMap.generateFlowField();

            // ver o tile q o rato tá
            // auto [x, y] = rat.getPosition();
            // auto [a, b] = tileMap.pixelsToTileGrid(Vector2f(x, y));
            // Tile rat_tile = tileMap.getTile(b, a);
            
            // // pegar o vetor de mov. desse tile e atualizar a pos do rato
            // Vector2f vector = rat_tile.getFlowDirection();
            // rat.move(vector);

            // Atualizando a posição do rato
            litter.update(window.getSize());
            litter2.update(window.getSize());

            // Atualizando a posição do jogador
            Time deltaTime = clock.restart();
            player.move(deltaTime, tileMap,window.getSize());


            window.clear();
            
            tileMap.draw(window);
            player.draw(window);
            litter.draw(window);
            litter2.draw(window);
            tileMap.drawFlowField(window);

            //verifica se o player chegou no objetivo
            if(tileMap.verifyPosition(player.getPosition()) == GOAL){
                cout << "Player chegou no objetivo" << endl;
                cout << current_map + 1 << endl;
                current_map = (current_map + 1); // Cicla entre os mapas disponíveis
                cout << "Carregando mapa " << current_map << endl;
                cout << "assets/map"+to_string(current_map)+".csv" << endl;
                tileMap.loadMap("assets/map"+to_string(current_map)+".csv");
                player.setPosition(tileMap.getInitPlayerPosition(), window.getSize());
            }

            window.display();
        }
        
    }
        
        

    return 0;
}
