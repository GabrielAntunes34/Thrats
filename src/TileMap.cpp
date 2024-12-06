#include "../include/TileMap.hpp"

// Construtor
TileMap::TileMap(Texture &atlas, Vector2u screenSize) {
    // Inicializando as grades lógica e de renderização
    this->tiles.assign(TILE_MAP_H, std::vector<Tile>(TILE_MAP_W, Tile()));
    this->vertexArray.setPrimitiveType(Quads);

    // Salvando os parâmetros informados
    this->tileAtlas = atlas;
    this->screenSize = screenSize;

    // LEMBRAR DE AJUSTAR O ASPECT RATIO OU NA MAIN, OU EM ALGUM ARQUIVO DE CONFIG
}