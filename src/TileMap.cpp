
#include "../include/TileMap.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <cstdio>
#include <iostream>


////////////////////////////////
//          auxiliares        //
////////////////////////////////


// Lê e já instancia os tiles do tileMap
vector<vector<int>> readCsv(const string& fileName) {
    ifstream file(fileName);
    vector<vector<int>> contents(TILE_MAP_H, vector<int>(TILE_MAP_W));
    string line;    // Auxiliar para ler cada linha do CSV
    int i = 0, j = 0;       // Auxiliares para os index da matriz
    
    // Verificando se o arquivo foi aberto
    if(!file.is_open()) {
        cerr << "Um erro ocorreu ao ler o CSV: " << fileName << endl;
        return {};
    }

    // Lendo os números do tileMap e guradando na matriz
    while(getline(file, line)) {
        stringstream ss(line);   // Iterador para parsear a string
        string value;
                    // Auxiliar que mantem o valor lido
        j = 0;
        
        // Guardando os valores convertidos para inteiros na matriz
        while(getline(ss, value, ',')) {
            contents[i][j] = stoi(value);
            j++;
        }
        i++;
    }
    file.close();

    return contents;
}

// Auxiliar que adequa o tamanho de cada Tile as dimensões da tela
int calculateTileSize(Vector2u screenSize) {
    return min(screenSize.x / TILE_MAP_W, screenSize.y / TILE_MAP_H);
}


////////////////////////////////
//          métodos           //
////////////////////////////////

// Construtor
TileMap::TileMap(Vector2u screenSize) {
    // Inicializando as grades lógica e de renderização
    this->tiles.assign(TILE_MAP_H, vector<Tile>(TILE_MAP_W, Tile()));

    // Salvando os parâmetros informados
    //this->tileAtlas = &tileAtlas;
    this->tileSize = calculateTileSize(screenSize);
    this->enemiesPositions = vector<Vector2u>();

    // CARREGANDO TEXTURAS

    // Carregando a textura do chão
    if(!this->groundTexture.loadFromFile("assets/ground.png")) {
        cerr << "Erro ao carregar a textura do chão" << endl;
    }

    // textura obstaculo (temporária)
    RectangleShape rectangle(Vector2f(this->tileSize, this->tileSize)); // Define o tamanho do retângulo
    rectangle.setFillColor(Color::Blue); // Define a cor do retângulo como azul

    RenderTexture renderTexture;
    renderTexture.create(50, 50); // Tamanho da textura
    renderTexture.clear(Color::Transparent);
    renderTexture.draw(rectangle);
    renderTexture.display();
    this->obstacleTexture = renderTexture.getTexture(); // Salva a textura de obstáculos como membro da classe

    // LEMBRAR DE AJUSTAR O ASPECT RATIO OU NA MAIN, OU EM ALGUM ARQUIVO DE CONFIG
}

// Função que converte coordenadas no tile map em coordenadas da tela (pixels)
Vector2u TileMap::tileGridToPixel(int i, int j) {
    Vector2u screenPos;
    screenPos.x = (int) i * this->tileSize + (this->tileSize / 2);
    screenPos.y = (int) j * this->tileSize + (this->tileSize / 2);
    return screenPos;
}
// Função que converte coordenadas no tile map em coordenadas da tela (pixels)
pair<int, int> TileMap::pixelsToTileGrid(Vector2u position) {
    pair<int, int> gridPos;
    gridPos.first = (int) (position.x - (this->tileSize / 2)) / this->tileSize;
    gridPos.second = (int) (position.y - (this->tileSize / 2)) / this->tileSize;
    return gridPos;
}


// Dado o nome de um CSV, essa função mapeaia todos os tiles lógicos e gráficos do nível
bool TileMap::loadMap(const string &fileName) {
    vector<vector<int>> csvMatrix;

    // Lendo o CSV e instanciando os tiles lógicos (por enquanto)
    csvMatrix = readCsv(fileName);

    if(csvMatrix.empty()) {
        return false;
    }
    for(int i = 0; i < TILE_MAP_H; i++) {

        for(int j = 0; j < TILE_MAP_W; j++) {
            this->tiles[i][j].setId(csvMatrix[i][j]);

            switch(this->tiles[i][j].getId()) {
            case PLAYER:
                this->initPlayerPosition = tileGridToPixel(i, j);
                this->tiles[i][j].setSprite(this->tileTexture); // sprite do chão
                break;

            case ENEMY:
                this->enemiesPositions.push_back(Vector2u(i, j));
                this->tiles[i][j].setSprite(this->tileTexture); // Sprite de chão/ spawn do ratinho
                break;
            
            case OBSTACLE:
                this->tiles[i][j].setTaniblity(true);
                this->tiles[i][j].setSprite(this->obstacleTexture);  // Sprite do obstáculo
                break;
            default:
                this->tiles[i][j].setSprite(this->groundTexture);  // Ground
                break;
            }
        }
        cout << endl;
    }
    return true;
}

// Desenhando os tiles na tela, pegando a posição de cada um e colocando em relaçao ao tamanho do tile
void TileMap::draw(RenderWindow &window){
    for(int i = 0; i < TILE_MAP_H; i++) {
        
        for(int j = 0; j < TILE_MAP_W; j++){
            this->tiles[i][j].getSprite().setPosition(j*tileSize, i*tileSize);
            window.draw(this->tiles[i][j].getSprite());
        }
    }    

}
