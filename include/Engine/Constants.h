// Constants

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

constexpr std::string WINDOW_TITLE = "Hit The Ball!";
constexpr sf::Vector2u WINDOW_SIZE(600, 600);

constexpr int CIRCLE_RADIUS = 30;
constexpr sf::Vector2f CIRCLE_START_POS(300, 300);

constexpr std::string TOTAL_HITS = "Total Hits: ";
const std::string START_TEXT = 
    "Hit the ball!"
    "\nPress E to start or Escape"
    "\nto close the game!";
