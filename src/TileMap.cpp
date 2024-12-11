
#include "../include/TileMap.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdio>
#include <iostream>
#include <queue>
#include <cmath>

#define infy 9999999.0f

////////////////////////////////
//          auxiliares        //
////////////////////////////////

struct Node{
    unsigned int x, y;
    float distance;
    bool operator>(const Node& other) const { //permite comparar dois nodes
        return distance > other.distance;
    }
};

void TileMap::generateIntegrationField(Vector2f goalFloat){

    Vector2u goal = Vector2u((unsigned int)goalFloat.x, (unsigned int)goalFloat.y);
    //Primeiro, inicializando todas as distancias com infinito
    for(int y = 0; y < TILE_MAP_H; y++){
        for(int x = 0; x < TILE_MAP_W; x++){
            tiles[y][x].setDistance(infy);
        }
    }

    //o goal tem distancia 0
    if(goal.y < TILE_MAP_H && goal.x < TILE_MAP_W){
        tiles[goal.y][goal.x].setDistance(0.0f);
    }else{
        //goal fora do mapa, nao faz nada
        return;
    }

    //fila de prioridade para o algoritmo de Dijkstra (min heap)
    priority_queue<Node, vector<Node>, greater<Node>> frontier;
    frontier.push({static_cast<unsigned int>(goal.x), static_cast<unsigned int>(goal.y), 0.0f}); //adiciona o goal na fila

    //Vizinhos (8-direçoes)
    vector<pair<int,int>> directions = {
        {1,0}, {0,1}, {-1,0}, {0,-1},
        {1,1}, {-1,1}, {1,-1}, {-1,-1}
    };

    while(!frontier.empty()){
        Node current = frontier.top();
        frontier.pop();

        //Se a distancia atual for maior que a distancia no tile, ja esta desatualizado
        if(current.distance > tiles[current.y][current.x].getDistance()){
            continue;
        }

        //Para cada vizinho
        for(auto &dir : directions){
            int nx = current.x + dir.first;
            int ny = current.y + dir.second;

            //verifica limites do mapa
            if(nx < 0 | nx >= (int)TILE_MAP_W || ny < 0 || ny >= (int)TILE_MAP_H){
                continue;
            }
            //calcula a nova distancia
            float newDist = current.distance + tiles[ny][nx].getCost();
            if(newDist < tiles[ny][nx].getDistance()){
                tiles[ny][nx].setDistance(newDist);
                frontier.push({(unsigned int)nx, (unsigned int)ny, newDist}); //adiciona na fila, unsigned int para evitar warnings
            }
        }
    }
    // Ao final, cada tile tera a distancia do goal
}


void TileMap::generateFlowField(){
    //para gerar o flow field, olhamos para cada tile e calculamos a direçao do menor custo

    //Vizinhos (8-direçoes)
    vector<pair<int,int>> directions = {
        {1,0}, {0,1}, {-1,0}, {0,-1},
        {1,1}, {-1,1}, {1,-1}, {-1,-1}
    };

    for (int y=0; y< TILE_MAP_H; y++){
        for(int x = 0; x <TILE_MAP_W; x++){
            float currentDist = tiles[y][x].getDistance();

            //se a distancia for infinita, significa que nao temos como chegar la
            //podemos definir o flowDirectionm como (0,0)
            if(currentDist == infy){
                // esse cara eh um obstaculo
                // tenho q ver para onde a seta aponta
                Vector2f dir = Vector2f(0.0f, 0.0f);

                if (y+1 >= TILE_MAP_H) {
                    if (tiles[y-1][x].getId() != OBSTACLE) {
                        dir.y = 1;
                    }
                    if (x+1 >= TILE_MAP_W) {
                        if (tiles[y][x-1].getId() != OBSTACLE) {
                            dir.x = -1;
                        }
                    } else {
                        if (tiles[y][x+1].getId() != OBSTACLE) {
                            dir.x = 1;
                        }
                        if (x-1 >= 0) {
                            if (tiles[y][x-1].getId() != OBSTACLE) {
                                dir.x = -1;
                            }
                        }
                    }
                } else {
                    if (tiles[y+1][x].getId() != OBSTACLE) {
                        dir.y = 1;
                    }
                    if (y-1 >= 0) {
                        if (tiles[y-1][x].getId() != OBSTACLE) {
                            dir.y = -1;
                        }
                    }
                    if (x+1 >= TILE_MAP_W) {
                        if (tiles[y][x-1].getId() != OBSTACLE) {
                            dir.x = -1;
                        }
                    } else {
                        if (tiles[y][x+1].getId() != OBSTACLE) {
                            dir.x = 1;
                        }
                        if (x-1 >= 0) {
                            if (tiles[y][x-1].getId() != OBSTACLE) {
                                dir.x = -1;
                            }
                        }
                    }
                }

                tiles[y][x].setFlowDirection(dir);
                continue;
            }

            float bestDist = currentDist;
            int bestX = x;
            int bestY = y;

            //checa os vizinhos para ver qual tem o menor custo

            for(auto &dir : directions){
                int nx = x + dir.first;
                int ny = y + dir.second;

                //verifica limites do mapa
                if(nx < 0 || nx >= (int)TILE_MAP_W || ny < 0 || ny >= (int)TILE_MAP_H){
                    continue;
                }

                float newDist = tiles[ny][nx].getDistance();
                if(newDist < bestDist){
                    bestDist = newDist;
                    bestX = nx;
                    bestY = ny;
                }
            }

            // Agora bestX e bestY indicam o vizinho com menor distancia
            // se forem iguais a (x,y), significa que este tile é o objetivo ou nao encontrou melhor vizinho
            if(bestX == x && bestY == y){
                //este é o tile objetivo
                tiles[y][x].setFlowDirection(Vector2f(0.0f, 0.0f));
            }else{
                // Cria um vetor da posiçao atual para a posiçao do melhor vizinho
                Vector2f flowDir = Vector2f((float)(bestX - x), (float)(bestY - y));
                
                // Normaliza o vetor
                float norm = sqrt(flowDir.x*flowDir.x + flowDir.y*flowDir.y);
                if (norm > 0.0f){
                    flowDir.x /= norm;
                    flowDir.y /= norm;
                }
                tiles[y][x].setFlowDirection(flowDir);
            }
        }
    }
}


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
    this->enemiesPositions = vector<Vector2f>();

    // CARREGANDO TEXTURAS

    // Carregando a textura do chão
    if(!this->groundTexture.loadFromFile("assets/ground.png")) {
        cerr << "Erro ao carregar a textura do chão" << endl;
    }

    // textura obstaculo 
    if(!this->obstacleTexture.loadFromFile("assets/caixa_cima.png")) {
        cerr << "Erro ao carregar a textura do obstáculo" << endl;
    }
    // textura do objetivo
    if(!this->goalTexture.loadFromFile("assets/luz.png")) {
        cerr << "Erro ao carregar a textura do objetivo" << endl;
    }    

    // LEMBRAR DE AJUSTAR O ASPECT RATIO OU NA MAIN, OU EM ALGUM ARQUIVO DE CONFIG
}


// Função que converte coordenadas no tile map em coordenadas da tela (pixels)
Vector2f TileMap::tileGridToPixel(int i, int j) {
    Vector2f screenPos;
    screenPos.x = i * this->tileSize + (this->tileSize / 2);
    screenPos.y = j * this->tileSize + (this->tileSize / 2);
    return screenPos;
}
// Função que converte coordenadas no tile map em coordenadas da tela (pixels)
pair<int, int> TileMap::pixelsToTileGrid(Vector2f position) {
    pair<int, int> gridPos;
    gridPos.first = (int) (position.x - (this->tileSize / 2)) / this->tileSize;
    gridPos.second = (int) (position.y - (this->tileSize / 2)) / this->tileSize;
    return gridPos;
}


// funcao que pega (i,j) da matriz de tiles do TileMap e devolve o Tile
Tile TileMap::getTile(int i, int j) {
    return tiles[i][j];
}


// Dado o nome de um CSV, essa função mapeaia todos os tiles lógicos e gráficos do nível
bool TileMap::loadMap(const string &fileName) {
    cout << "Carregando mapa: " << fileName << endl;
    vector<vector<int>> csvMatrix;

    // Lendo o CSV e instanciando os tiles lógicos (por enquanto)
    csvMatrix = readCsv(fileName);

    if(csvMatrix.empty()) {
        return false;
    }

    float correcaoEscala = tileSize/16.0f;

    for(int i = 0; i < TILE_MAP_H; i++) {

        for(int j = 0; j < TILE_MAP_W; j++) {
            this->tiles[i][j].setId(csvMatrix[i][j]);

            switch(this->tiles[i][j].getId()) {
            case PLAYER:
                this->initPlayerPosition = tileGridToPixel(i, j);
                this->tiles[i][j].setSprite(this->groundTexture, correcaoEscala); // sprite do chão
                this->tiles[i][j].setCost(1.0f);
                break;

            case ENEMY:
                this->enemiesPositions.push_back(Vector2f(j, i));
                this->tiles[i][j].setSprite(this->groundTexture, correcaoEscala); // Sprite de chão/ spawn do ratinho
                this->tiles[i][j].setCost(1.0f);
                break;
            
            case OBSTACLE:
                this->tiles[i][j].setTaniblity(true);
                this->tiles[i][j].setSprite(this->obstacleTexture, correcaoEscala);  // Sprite do obstáculo
                this->tiles[i][j].setCost(infy);

                break;

            case GOAL:
                this->tiles[i][j].setSprite(this->goalTexture, correcaoEscala);
                this->tiles[i][j].setCost(1.0f);
                break;
            default:
                this->tiles[i][j].setSprite(this->groundTexture, correcaoEscala);  // Ground
                this->tiles[i][j].setCost(1.0f);
                break;
            }
        }
    }
    return true;
}

//retornar a posicao inicial do jogador
Vector2f TileMap::getInitPlayerPosition(){
    return this->initPlayerPosition;
}   

//retorna se a posicao é um objetivo
int TileMap::verifyPosition(Vector2f position) {
    pair<int, int> gridPos = pixelsToTileGrid(position);
    switch (tiles[gridPos.second][gridPos.first].getId()) {
        case OBSTACLE:
            return OBSTACLE;
        case GOAL:
            return GOAL;
        default:
            return 0;
    }
}

int TileMap::getTileSize() {
    return this->tileSize;
}

vector<Vector2f> TileMap::getEnemiesPositions() {
    return this->enemiesPositions;
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

void TileMap::drawFlowField(RenderWindow &window){
    for(int i = 0; i < TILE_MAP_H; i++) {
        
        for(int j = 0; j < TILE_MAP_W; j++){
            // Posição do centro do tile
        float cx = j * tileSize + tileSize / 2.0f;
        float cy = i * tileSize + tileSize / 2.0f;

        Vector2f dir = tiles[i][j].getFlowDirection();

        // Se a direção é zero, pode significar objetivo ou obstáculo. Vamos ignorar
        if (fabs(dir.x) < 0.0001f && fabs(dir.y) < 0.0001f) {
            continue;
        }

        // Cria uma linha para representar a direção
        // Começa no centro do tile e vai 10 pixels na direção do flow
        float length = 10.0f; // tamanho da "seta"
        Vertex line[2];
        line[0] = Vertex(Vector2f(cx, cy), Color::Red);
        line[1] = Vertex(Vector2f(cx + dir.x * length, cy + dir.y * length), Color::Red);

        window.draw(line, 2, Lines);

        // Opcionalmente, desenhar uma pequena cabeça de seta
        // Para simplificar, um pequeno V:
        Vector2f perp(-dir.y, dir.x); // vetor perpendicular
        float arrowSize = 3.0f;
        Vertex arrow[2];
        arrow[0] = Vertex(line[1].position, Color::Red);
        arrow[1] = Vertex(line[1].position - dir * 3.0f + perp * arrowSize, Color::Red);
        window.draw(arrow, 2, Lines);

        Vertex arrow2[2];
        arrow2[0] = Vertex(line[1].position, Color::Red);
        arrow2[1] = Vertex(line[1].position - dir * 3.0f - perp * arrowSize, Color::Red);
        window.draw(arrow2, 2, Lines);
        }
    }
}