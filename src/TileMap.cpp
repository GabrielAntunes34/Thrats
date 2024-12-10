#include "../include/TileMap.hpp"

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
    string line;
    while(getline(file, line)) {
        stringstream ss(line);   // Iterador para parsear a string
        string value;            // Auxiliar que mantem o valor lido

        // Guardando os valores convertidos para inteiros na matriz
        while(getline(ss, value, ',')) {
            contents[i][j] = stoi(value);
            i++;
        }
        j++;
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
TileMap::TileMap(Texture &atlas, Vector2u screenSize) {
    // Inicializando as grades lógica e de renderização
    this->tiles.assign(TILE_MAP_H, vector<Tile>(TILE_MAP_W, Tile()));

    // Salvando os parâmetros informados
    this->tileAtlas = atlas;
    this->tileSize = calculateTileSize(screenSize);
    this->enemiesPositions = vector<Vector2u>();

    // LEMBRAR DE AJUSTAR O ASPECT RATIO OU NA MAIN, OU EM ALGUM ARQUIVO DE CONFIG
}

// Dado o nome de um CSV, essa função mapeaia todos os tiles lógicos e gráficos do nível
bool TileMap::loadMap(const string &fileName) {
    vector<vector<int>> csvMatrix;

    // Lendo o CSV e instanciando os tiles lógicos (por enquanto)
    csvMatrix = readCsv(fileName);
    for(int i = 0; i < TILE_MAP_H; i++) {
        for(int j = 0; j < TILE_MAP_W; j++) {
            this->tiles[i][j].setId(csvMatrix[i][j]);

            switch(this->tiles[i][j].getId()) {
            case PLAYER:
                this->initPlayerPosition = tileGridToPixel(i, j);
                this->tiles[i][j].setSprite(); // sprite do chão
                break;

            case ENEMY:
                this->enemiesPositions.push_back(Vector2u(i, j));
                this->tiles[i][j].setSprite(); // Sprite de chão/ spawn do ratinho
                break;
            
            case OBSTACLE:
                this->tiles[i][j].setTangiblity(true);
                this->tiles[i][j].setSprite();  // Sprite do obstáculo
            
                this->tiles[i][j].setSprite();  // Sprie do chão

            default:
                this->tiles[i][j].setSprite();  // Ground
                break;
            }
        }
    }



}
