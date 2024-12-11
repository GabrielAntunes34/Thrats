#include "../include/Menu.hpp"
#include "../include/TileMap.hpp"

Menu::Menu(sf::RenderWindow &window, const string &fontPath) :
window(window), selectedIndex(0) {
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Failed to load font");
    }

    sf::Text title("Bem vindo :)", font, 64);
    sf::Text subtitle("Aperte Enter para comecar a jogar!", font, 32);

    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 100);

    subtitle.setOrigin(subtitle.getLocalBounds().width / 2, subtitle.getLocalBounds().height / 2);
    subtitle.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 100);

    menuText.push_back(title);
    menuText.push_back(subtitle);
}

int Menu::run(TileMap tileMap) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    return 0; 
                }
            }
        }

        // Renderizar o menu
        window.clear(sf::Color::Black);

        sf::RectangleShape background(sf::Vector2f(window.getSize().x*0.5, window.getSize().y*0.5)); // Tamanho do retângulo
        background.setFillColor(sf::Color(0, 0, 0, 150)); // Preto com 150 de alfa (transparência)
        background.setOrigin(background.getLocalBounds().width / 2, background.getLocalBounds().height / 2);
        background.setPosition(window.getSize().x/2, window.getSize().y/2); // Posicionar no meio da tela

        tileMap.draw(window);
        window.draw(background);
        for (const auto &text : menuText) {
            window.draw(text);
        }
        window.display();
    }
    return -1;
}