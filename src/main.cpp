#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <ostream>
#include <thread>
#include <mutex>
#include <semaphore.h>
#include <string>
#include <vector>

#include "../include/TileMap.hpp"
#include "../include/Rat.h"
#include "../include/Menu.hpp"
#include "../include/Player.hpp"
#include "../include/Litter.hpp"


using namespace sf;
using namespace std;


#define MAPS_AVAILABLE 10

// Inicializa o vetor de ninhadas
void initLitters(vector<Litter> &litters, TileMap &tileMap, int size) {
    for(int i = 0; i < size; i++) {
        litters.push_back(Litter(tileMap.getEnemiesPositions()[i], 20, tileMap));
    } 
}

void initLitterThreads(vector<thread> &threads, vector<Litter> &litters, Player &player, RenderWindow &window, bool &running, mutex &mtx) {
    // Inicializando uma nova thread para cada ninhada
    for(int i = 0; i < litters.size(); i++) {
        threads.push_back(thread([&litters, &window, &player, i, &running, &mtx](){
            while(true) {
                bool death = false;

                // Verificando se é possiível mudar as threads!
                mtx.lock();
                    if(!running) {
                        mtx.unlock();
                        break;
                    }

                    // Se sim, atualizamos os ratos
                    death = litters[i].update(window.getSize(), player.getBounds());

                    if(death || !player.isAlive()) {
                        player.setLife(false);
                        mtx.unlock();
                        break;
                    }
                mtx.unlock();

            
                this_thread::sleep_for(chrono::milliseconds(16));
            }
        }));
    }
}

void clearLitterThreads(vector<thread> &threads) {
    for(int i = 0; i < threads.size(); i++) {
        threads[i].detach();
    }
}

int main() {
    VideoMode desktop = VideoMode::getDesktopMode(); // Tamanho da tela
    Clock clock;                                     // clock global do jogo
 
    // ===============
    // JANELA
    // ===============

    RenderWindow window(sf::VideoMode(desktop), "Threads - The Game!");
    window.setFramerateLimit(60); // Limita a janela a 60 FPS

    // ===============
    // TILEMAP
    // ===============

    int current_map = 1; //MAPA ATUAL
    TileMap tileMap(window.getSize());
    tileMap.loadMap("assets/map"+to_string(current_map)+".csv");

    // =================
    // Player
    // =================    
    Texture tex;
    if(!tex.loadFromFile("assets/bruno_antunes_barbosa.png")) {
        cerr << "Falha ao carregar a textura do player" << endl;
        exit(1);
    }

    // cria o player
    Player player(Vector2f(0.f, 0.f), tex, tileMap.getTileSize());
    player.setPosition(tileMap.getInitPlayerPosition(), window.getSize());

    // ===============
    // NINHADAS E THREADS
    // ===============

    // Variáveis do sincronismo
    bool levelRunning = true;     // Indica quando o jogo requer que as threads atualizem os ratos
    mutex mtx;
    //sem_t deathSemaphore;

    // Variáveis de controle das ninhadas
    vector<Litter> litters;
    vector<thread> littersThreads;
    int littersInLevel = tileMap.getEnemiesPositions().size();

    // Instanciando ninhadas e threads
    initLitters(litters, tileMap, littersInLevel);
    initLitterThreads(littersThreads, litters, player, window, levelRunning, mtx);    
    clearLitterThreads(littersThreads);

    // =================
    // MENU
    // =================

    // Mostrar o menu e obter a seleção
    Menu menu(window, "assets/Pixeled.ttf");
    int menuSelection = menu.run(tileMap);

    // =================
    // Game loop
    // =================
    while (window.isOpen())
    {
        if (menuSelection == 0) {
            mtx.lock();
                levelRunning = true;
            mtx.unlock();

            //eventos
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed) {
                    mtx.lock();
                        levelRunning = false;
                    mtx.unlock();
                    window.close();
                }
            }

            // Fazendo o flow field
            Vector2f goal = player.getPosition();
            // converter goal para pixelsToTileGrid
            Vector2f goalTilePos = Vector2f(tileMap.pixelsToTileGrid(goal).first,
                                            tileMap.pixelsToTileGrid(goal).second);

            tileMap.generateIntegrationField(goalTilePos);
            tileMap.generateFlowField();

            // Atualizando a posição do jogador
            Time deltaTime = clock.restart();
            player.move(deltaTime, tileMap,window.getSize());

            // Redesenhando tudo na tela
            window.clear();
            tileMap.draw(window);
            player.draw(window);

            for(int i = 0; i < littersInLevel; i++) {
                litters[i].draw(window);
            }

            //verifica se o player chegou no objetivo
            if(tileMap.verifyPosition(player.getPosition()) == GOAL){
                // Atualizando o índice de mapas
                mtx.lock();
                current_map = (current_map + 1);
                if(current_map == 11)
                    current_map = 1;

                tileMap.loadMap("assets/map"+to_string(current_map)+".csv");


                // resetando a posição do player e dos Litters
                player.setPosition(tileMap.getInitPlayerPosition(), window.getSize());
                litters.clear();
                littersInLevel = tileMap.getEnemiesPositions().size();
                initLitters(litters, tileMap, littersInLevel);

                // Initicializando as novas threads
                initLitterThreads(littersThreads, litters, player, window, levelRunning, mtx);
                mtx.unlock();
            }

            // Verificando se o player morreu :(
            if(!player.isAlive()) {
                mtx.lock();
                    // Limpando as threads atuais e o vetor de litters
                    //clearLitterThreads(littersThreads);
                    litters.clear();

                    // Voltando o jogo ao estado inicial da fase em questão
                    player.setPosition(tileMap.getInitPlayerPosition(), window.getSize());
                    player.setLife(true);
                    initLitters(litters, tileMap, littersInLevel);

                    // Reinicializando as threads
                    initLitterThreads(littersThreads, litters, player, window, levelRunning, mtx);
                mtx.unlock();
            }

            window.display();
        }
        
    }
        
    // Encerrando as threads
    mtx.lock();
        levelRunning = false;
    mtx.unlock();
    for(int i = 0 ; i < littersInLevel; i++) {
        if(littersThreads[i].joinable())
        littersThreads[i].join();
    }

    return 0;
}
