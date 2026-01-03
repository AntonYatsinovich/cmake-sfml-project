#include <iostream>
#include <random>
#include <format>
#include <optional> 
#include <SFML/Graphics.hpp>
#include "Engine/Constants.h"

// Генератор чисел
namespace {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
}

// Логика и отрисовка игры
class Game {
private:
    // Поля окна, шрифта и текста
    sf::RenderWindow window;
    sf::Font font;
    sf::CircleShape circle;
    sf::Text total_hits;
    sf::Text start_text;
    
    int count; // Счётчик попаданий игрока
    bool is_game; // Состояние игры (главное меню/сама игра)
    
    // Генерация чисел в нужном диапазоне
    std::uniform_real_distribution<float> dist_x;
    std::uniform_real_distribution<float> dist_y;

    // Обработка системных событий
    void processEvents() {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close(); // Если игрок нажал "Закрыть окно" - оно закроется
            }

            handleKeyboard(event);
            handleMouse(event);
        }
    }
    
    // Обработка ввода с клавиатуры
    void handleKeyboard(const std::optional<sf::Event>& event) {
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            // Закрытие на Escape
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
            }
            // Старт игры на клавишу 'E'
            else if (keyPressed->scancode == sf::Keyboard::Scancode::E) {
                is_game = true;
            }
        }
    }
    
    // Логика взаимодействия с мышью
    void handleMouse(const std::optional<sf::Event>& event) {
        if (!is_game) return; // Мышка доступна только во время самой игры

        if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouse->button == sf::Mouse::Button::Left) {
                // Проверка: попал ли клик по кругу
                if (circle.getGlobalBounds().contains(sf::Vector2f(mouse->position))) {
                    count++;
                    // Перемещение круга в новую случайную позицию
                    circle.setPosition({dist_x(gen), dist_y(gen)});
                    total_hits.setString(std::format("Total Hits: {}", count));
                }
            }
        }
    }
    
    // Отрисовка игры
    void render() {
        window.clear(sf::Color::Black);
    
        if (!is_game) {
            window.draw(start_text);
        }
        else {
            window.draw(circle);
            window.draw(total_hits);
        }

        window.display();
    }

public:

    // Конструктор
    Game() :
        window(sf::VideoMode(WINDOW_SIZE), WINDOW_TITLE),
        font("assets/fonts/Space_Mono/SpaceMono-Regular.ttf"),
        circle(CIRCLE_RADIUS),
        total_hits(font, TOTAL_HITS),
        start_text(font, START_TEXT),
        count(0),
        is_game(false),
        // Расчет диапазона так, чтобы круг не выходил за границы окна
        dist_x(0.f, static_cast<float>(WINDOW_SIZE.x) - (CIRCLE_RADIUS * 2)),
        dist_y(0.f, static_cast<float>(WINDOW_SIZE.y) - (CIRCLE_RADIUS * 2))
    {
        window.setFramerateLimit(60); // Ограничение FPS для стабильности
        circle.setPosition(CIRCLE_START_POS);
        circle.setFillColor(sf::Color::White);
    }
    
    // Точка входа в игровой цикл
    void run() {
        while (window.isOpen()) {
            processEvents();
            render();
        }
    }
};

int main() {
    try {
        Game game;
        game.run();
    } catch (const std::exception& e) {
        // Вывод ошибок в стандартный поток ошибок
        std::cerr << std::format("Fatal Error: {}\n", e.what()); // я не знаю что делает e.what()
        return 1;
    }

    return 0;
}
