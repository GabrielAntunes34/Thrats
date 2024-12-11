#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"

#define TILE_MAP_W 40
#define TILE_MAP_H 22

using namespace sf;
using namespace std;

class TileMap {
    private:
        vector<vector<Tile>> tiles;         // Matriz de tiles lógicos
        //VertexArray vertexArray;          // Array do mapa a ser renderizado
        //Texture tileAtlas;                  // Referencia a imagem, na memória, com todos os sprites
        
        
        Texture tileTexture;
        Texture groundTexture; 
        Texture obstacleTexture;
        Texture goalTexture;

        Vector2f initPlayerPosition;        // Posição inicial do jogador
        vector<Vector2f> enemiesPositions;   // Lista coms as posições iniciais de cada grupo de ratos
        int tileSize;                       // Tamaho da tela, para ajuste do aspect ratio

    public:
        TileMap(Vector2u screenSize);

        // Operações entre tela e tileMap
        Vector2f tileGridToPixel(int i, int j);
        pair<int, int> pixelsToTileGrid(Vector2f position);

        Vector2f getInitPlayerPosition();
        Tile getTile(int i, int j);

        int getTileSize();


        int verifyPosition(Vector2f position);

        // Operações do tileMap
        bool loadMap(const string &fileName);
        void draw(RenderWindow &window);
        void drawFlowField(RenderWindow &window);

        
        // para pathfinding
        void generateIntegrationField(Vector2f goal);
        void generateFlowField();

};


#endif