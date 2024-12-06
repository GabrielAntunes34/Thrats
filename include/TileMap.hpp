#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"

#define TILE_MAP_W 40
#define TILE_MAP_H 22

using namespace sf;

class TileMap {
    private:
        std::vector<std::vector<Tile>> tiles;   // Matriz de tiles lógicos
        VertexArray vertexArray;                // Array do mapa a ser renderizado
        Texture tileAtlas;                      // Referencia a imagem, na memória, com todos os sprites
        Vector2u screenSize;                    // Tamaho da tela, para ajuste do aspect ratio

    public:
        TileMap(Texture &atlas, Vector2u screenSize);

        bool loadMap(std::string &mapName);
        void draw(RenderWindow &window);

};


#endif