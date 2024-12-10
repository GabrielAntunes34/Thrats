#ifndef TILEMAP_H
#define TILEMAP_H

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
        Texture tileAtlas;                  // Referencia a imagem, na memória, com todos os sprites
        Vector2u initPlayerPosition;        // Posição inicial do jogador
        vector<Vector2u> enemiesPositions;   // Lista coms as posições iniciais de cada grupo de ratos
        int tileSize;                       // Tamaho da tela, para ajuste do aspect ratio

    public:
        TileMap(Texture &atlas, Vector2u screenSize);

        // Operações entre tela e tileMap
        Vector2u tileGridToPixel(int i, int j);
        pair<int, int> pixelsToTileGrid(Vector2u position);

        // Operações do tileMap
        bool loadMap(const string &fileName);
        void draw(RenderWindow &window);

};


#endif