#ifndef LITTER_H
#define LITTER_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "../include/Rat.h"
#include "../include/TileMap.hpp"


// Classe que representa a ninhada de ratos (ela será utilizada pelas Threads)
// O objetivo é que a ninhada de ratos siga o jogador, ela utilizará o flow field para se movimentar
// A ideia é separa a movimentação dos grupos de ratos, para que possamos paralelizar o código
class Litter {
    // Atributos
    private:
        vector<Rat> rats;   // Vetor de ratos que compõem a ninhada
        int size;           // Tamanho da ninhada
        float gride_size;   // Tamanho do grid para movimentação
        Vector2f spawn;     // Posição de spawn da ninhada
        TileMap &tileMap;   // Referência ao tileMap relacioando a ninhada, responsável por gerar o flow field

    public:
        Litter(Vector2f spawn, int size, TileMap &tileMap);         // Construtor
        bool update(Vector2u screen_size, FloatRect playerBounds);  // Atualiza a posição da ninhada, retorna se houve colisão com o player e lida com colisao com outros ratos
        


        void draw(RenderWindow &window); // Desenha a ninhada na tela
};

#endif