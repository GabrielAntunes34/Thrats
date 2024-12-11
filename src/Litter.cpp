#include "../include/Litter.hpp"
#include <SFML/System/Vector2.hpp>
#include <unordered_map>

//funçao auxiliar
pair<int, int> getGridPosition(const Vector2f& position, float gridSize) {
    return { static_cast<int>(position.x / gridSize), static_cast<int>(position.y / gridSize) };
}


Litter::Litter(Vector2f spawn, int size,  TileMap &tileMap) 
    : spawn(spawn), size(size), tileMap(tileMap) { // Inicializando tileMap na lista de inicialização
    // Definir GRID_SIZE baseado no tileSize do tileMap
    const float GRID_SIZE = static_cast<float>(tileMap.getTileSize());
    this->gride_size = GRID_SIZE; // Certifique-se de inicializar gride_size

    // Reservar espaço para os ratos
    this->rats.reserve(size);

    for(int i = 0; i < this->size; i++) {
        // Pequena variação na posição inicial para evitar superposição exata
        float offsetX = static_cast<float>(rand() % 20 - 10); // -10 a 10
        float offsetY = static_cast<float>(rand() % 20 - 10); // -10 a 10

        Vector2f spawnReal = tileMap.tileGridToPixel(this->spawn.x, this->spawn.y);

        this->rats.emplace_back(spawnReal.x + offsetX, spawnReal.y + offsetY, 10.0f);
    }   
}

void Litter::update(Vector2u screen_size) {
    // Particionamento espacial: mapa de grid para os ratos
        unordered_map<long, vector<int>> spatialGrid; // Chave combinada de grid x e y
        for(int i = 0; i < rats.size(); ++i) {
            Vector2f pos = rats[i].getPosition();
            pair<int, int> gridPos = getGridPosition(pos, this->gride_size);
            long key = gridPos.first * 10000 + gridPos.second; // Supondo que o grid não excede 10000 em cada dimensão
            spatialGrid[key].push_back(i);
        }

        // Atualizar movimento dos ratos com separação
        for(int i = 0; i < this->rats.size(); ++i) {

            Rat& currentRat = this->rats[i];
            pair<int, int> tileGridPos = tileMap.pixelsToTileGrid(currentRat.getPosition());
            Tile currentTile = tileMap.getTile(tileGridPos.second, tileGridPos.first);
            Vector2f flow = currentTile.getFlowDirection();

            // Obtendo grid do rato atual
            Vector2f pos = currentRat.getPosition();
            pair<int, int> gridPos = getGridPosition(pos, this->gride_size);

            // Verificar ratos no mesmo grid e grids adjacentes
            vector<int> nearbyRats;
            for(int dx = -1; dx <= 1; ++dx) {
                for(int dy = -1; dy <= 1; ++dy) {
                    pair<int, int> adjacentGrid = { gridPos.first + dx, gridPos.second + dy };
                    long key = adjacentGrid.first * 10000 + adjacentGrid.second;
                    if(spatialGrid.find(key) != spatialGrid.end()) {
                        nearbyRats.insert(nearbyRats.end(), spatialGrid[key].begin(), spatialGrid[key].end());
                    }
                }
            }

            // Calcular força de separação
            Vector2f separation(0.f, 0.f);
            int neighborCount = 0;
            for(auto& j : nearbyRats) {
                if(i == j) continue; // Ignorar a si mesmo
                Vector2f otherPos = this->rats[j].getPosition();
                float distance = sqrt(pow(pos.x - otherPos.x, 2) + pow(pos.y - otherPos.y, 2));
                float minDistance = currentRat.getRadius() * 2.0f; // Distância mínima para evitar sobreposição

                if(distance < minDistance && distance > 0.f) {
                    // Direção de separação
                    Vector2f diff = pos - otherPos;
                    diff /= distance; // Normalizar
                    separation += diff;
                    neighborCount++;
                }
            }

            if(neighborCount > 0) {
                separation /= static_cast<float>(neighborCount);
                // Opcional: limitar a magnitude da força de separação
                float mag = sqrt(separation.x * separation.x + separation.y * separation.y);
                if(mag > 0.f) {
                    float desiredSeparation = 1.0f; // Ajuste conforme necessário
                    separation = (separation / mag) * desiredSeparation;
                }
            }

            // Mover o rato com o fluxo e a separação
            currentRat.move(flow, separation, screen_size);
        }
}

void Litter::draw(RenderWindow &window){
    for(auto& rat : this->rats) {
        rat.draw(window);
    }
}