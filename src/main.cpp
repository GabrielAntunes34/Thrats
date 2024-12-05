#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
using namespace sf;

int main()
{
    VideoMode desktop = VideoMode::getDesktopMode(); // Tamanho da tela

    RenderWindow window(sf::VideoMode(desktop), "Threads - The Game!");
    CircleShape shape(100.f); // Cria um círculo de raio 100
    shape.setFillColor(sf::Color::Green); // Preenche o círculo de verde

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
