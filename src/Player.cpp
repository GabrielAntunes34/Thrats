#include "../include/Player.hpp"

Player::Player(Vector2f initPosition, Texture &texture, int tileSize) {
    // Atributos lógicos
    this->alive = true;
    this->tangibility = true;
    this->moving = false;
    this->velocity = 0.f;
    this->currentDirection = Vector2f(0.f, 0.f);
    this->position = initPosition;

    // Atributos do sprite
    this->sprite.setTexture(texture);
    this->sprite.setScale(tileSize / 16, tileSize / 16 );
    this->size = 16 * this->sprite.getScale().x;
}

// Getters
Vector2f Player::getPosition() {
    return this->position;
}

bool Player::isAlive() {
    return this->alive;
}

bool Player::isTangible() {
    return this->tangibility;
}

// Setters
// Seta uma nova posição para o jogador, verificando se ele não saiu do tela
void Player::setPosition(Vector2f position, Vector2u screenSize) {
    // Verificações para permitir o movimento 
    // Fazer If da colisão com blocos!!!

    if(!(position.x < 0 || position.x  >= screenSize.x - this->size))
        this->position.x = position.x;
    if(!(position.y < 0 || position.y >= screenSize.y - this->size))
        this->position.y = position.y;

    // Movendo o sprite na tela
    this->sprite.setPosition(this->position);
}

void Player::setLife(bool lifeState) {
    this->alive = lifeState;
}

void Player::setTangibility(bool tangibility) {
    this->tangibility = tangibility;
}


// Mechanics
// Recebe o input dos usuário e move o personagem de acordo.
void Player::move(Time deltaTime, TileMap tileMap, Vector2u screenSize) {
    Vector2f newPosition;           // armazenará a posição final com o movimento
    float norma;                    // Auxiliar para corrigir movimentos horizontais

    // Obtendo o input do usuário
    if(Keyboard::isKeyPressed(Keyboard::W)) {
        this->currentDirection.y -= 1.f;
        this->moving = true;
    }
    if(Keyboard::isKeyPressed(Keyboard::D)) {
        this->currentDirection.x += 1.f;
        this->moving = true;
    }
    if(Keyboard::isKeyPressed(Keyboard::S)) {
        this->currentDirection.y += 1.f;
        this->moving = true;
    }
    if(Keyboard::isKeyPressed(Keyboard::A)) {
        this->currentDirection.x -= 1.f;
        this->moving = true;
    }

    //this->moving = true;
    //direction.x = 1.f;

    // Impedindo que as duas direções se acumulem em movimentos horizontais
    // Pela normalização do vetor
    if(this->currentDirection.x != 0.f || this->currentDirection.y != 0.f) {
        norma = sqrt(this->currentDirection.x * this->currentDirection.x + this->currentDirection.y * this->currentDirection.y);
        this->currentDirection /= norma;
    }

    // Atualizando a velocidade coforme o input
    if(this->moving) {
        this->velocity += ACELERATION * deltaTime.asSeconds();
        if(this->velocity > MAX_VELOCITY)
            this->velocity = MAX_VELOCITY;  // Limite superior da velocidade
    }
    else {
        if(this->velocity > 0.f) {
            this->velocity -= DECELERATION * deltaTime.asSeconds();
        }
        else {
            this->velocity = 0.f; // Limite inferiror da velocidade
            this->currentDirection.x = 0;
            this->currentDirection.y = 0;
        }
    }

    // Calculando newPosition
    newPosition = this->position + this->currentDirection * this->velocity * deltaTime.asSeconds();
    
    // Se não colidir com um obstáculo, atualizamos a posição
    if(tileMap.verifyPosition(newPosition) != OBSTACLE)
        this->setPosition(newPosition, screenSize);
    
    // Resetando "moving" para o próximo loop
    this->moving = false;
}

void Player::draw(RenderWindow &window) {
    window.draw(this->sprite);
}