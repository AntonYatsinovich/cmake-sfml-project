// Main.cpp

#include <iostream>
#include <random>
#include <format>
#include <SFML/Graphics.hpp>

// Генератор случайных чисел
std::random_device rd; 
std::mt19937 gen(rd());

int main()
{
    // Создание окна
    auto window = sf::RenderWindow(sf::VideoMode({600, 600}), "CMake SFML Project");
    window.setFramerateLimit(60);

    //
    int count = 0;

    // Создание круга
    sf::CircleShape circle(30);
    circle.setPosition({300, 300});

    // Определяем диапазон случайных чисел
    std::uniform_real_distribution<float> dist(0, window.getPosition().x - (circle.getRadius() * 2));

    sf::Font font("../../assets/fonts/Space_Mono/SpaceMono-Regular.ttf");
    sf::Text total_hits(font, "Total Hits: 0");

    while (window.isOpen())
    {
        // Обработчик Событий

        while (const std::optional event = window.pollEvent())
        {
            // Если игрок закроет игру, она завершится
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            
            // Если игрок нажмёт Escape, игра завершится
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
            }

            // Проверка на попадание мышкой по кругу
            else if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse->button == sf::Mouse::Button::Left) {
                    // Вычисление вектора от центра круга до позиции мышки
                    sf::Vector2f diff = sf::Vector2f(mouse->position) - (circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius()));

                    if (diff.lengthSquared() <= circle.getRadius() * circle.getRadius())
                    {
                        count++;
                        std::cout << "Попал!" << std::endl;
                        circle.setPosition({dist(gen), dist(gen)});
                        total_hits.setString(std::format("Total Hits: {}", count));
                    }
                }
            }
        }
        
        // Логика игры

        // Обработка графики игры

        window.clear(sf::Color::Black);

        window.draw(circle);
        window.draw(total_hits);

        window.display();
    }

    std::cout << "Игра завершилась" << std::endl;

    return 0;
}
