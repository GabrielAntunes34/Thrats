#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <vector>

#include "../include/Rat.h"

using namespace sf;
using namespace std;

int main()
{
    VideoMode desktop = VideoMode::getDesktopMode(); // Tamanho da tela

    RenderWindow window(sf::VideoMode(desktop), "Threads - The Game!");
    window.setFramerateLimit(60); // Limita a janela a 60 FPS
    CircleShape shape(100.f); // Cria um círculo de raio 100
    shape.setFillColor(sf::Color::Green); // Preenche o círculo de verde

    
    vector<Rat> rats;

    //criando ratos de exemplo
    for(int i = 0; i < 15; i++) {
        rats.push_back(Rat(50 * i, 50 * i, 20));
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        //faz os ratos se moverem
        for (auto&rat : rats) {
            rat.move();
        }


        window.clear();

        // Desenha os ratos
        for (auto&rat : rats) {
            rat.draw(window);
        }

        window.display();
    }

    return 0;
}
