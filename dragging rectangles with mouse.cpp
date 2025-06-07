// sudo apt install libsfml-dev
// g++ -std=c++17 main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o suorakulmiot

#include <SFML/Graphics.hpp>

bool rectanglesOverlap(const sf::RectangleShape& a, const sf::RectangleShape& b) {
    return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Vedettävät suorakulmiot");

    sf::RectangleShape rect1(sf::Vector2f(150, 100));
    rect1.setPosition(100, 100);
    rect1.setFillColor(sf::Color::Red);

    sf::RectangleShape rect2(sf::Vector2f(150, 100));
    rect2.setPosition(300, 200);
    rect2.setFillColor(sf::Color::Blue);

    sf::RectangleShape* dragging = nullptr;
    sf::Vector2f offset;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Sulje ikkuna
            if (event.type == sf::Event::Closed)
                window.close();

            // Hiiren painallus
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
                if (rect1.getGlobalBounds().contains(mousePos)) {
                    dragging = &rect1;
                    offset = rect1.getPosition() - mousePos;
                } else if (rect2.getGlobalBounds().contains(mousePos)) {
                    dragging = &rect2;
                    offset = rect2.getPosition() - mousePos;
                }
            }

            // Hiiren vapautus
            if (event.type == sf::Event::MouseButtonReleased) {
                dragging = nullptr;
            }

            // Hiiren liikuttaminen
            if (event.type == sf::Event::MouseMoved && dragging != nullptr) {
                sf::Vector2f newPos = (sf::Vector2f)sf::Mouse::getPosition(window) + offset;
                sf::Vector2f oldPos = dragging->getPosition();

                dragging->setPosition(newPos);

                // Estä päällekkäisyys
                if (rectanglesOverlap(rect1, rect2)) {
                    dragging->setPosition(oldPos);
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(rect1);
        window.draw(rect2);
        window.display();
    }

    return 0;
}
