#include "Map.h"

Map::Map() {
    boundaries[0].setSize(sf::Vector2f(MAP_WIDTH, BLOCK_SIZE));
    boundaries[0].setPosition(sf::Vector2f(0, 0));

    boundaries[1].setSize(sf::Vector2f(MAP_WIDTH, BLOCK_SIZE));
    boundaries[1].setPosition(sf::Vector2f(0, MAP_HEIGHT - BLOCK_SIZE));

    boundaries[2].setSize(sf::Vector2f(BLOCK_SIZE, MAP_HEIGHT));
    boundaries[2].setPosition(sf::Vector2f(0, 0));

    boundaries[3].setSize(sf::Vector2f(BLOCK_SIZE, MAP_HEIGHT));
    boundaries[3].setPosition(sf::Vector2f(MAP_WIDTH - BLOCK_SIZE, 0));

    for (int i = 0; i < 4; ++i) {
        boundaries[i].setFillColor(sf::Color::White);
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Map::draw(sf::RenderWindow& window) const {
    for (int i = 0; i < 4; ++i) {
        window.draw(boundaries[i]);
    }
}

bool Map::isColliding(const sf::FloatRect& rect) const {
    for (int i = 0; i < 4; ++i) {
        if (rect.intersects(boundaries[i].getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

sf::Vector2f Map::generateRandomPosition() const {
    int maxX = (MAP_WIDTH / BLOCK_SIZE) - 1;
    int maxY = (MAP_HEIGHT / BLOCK_SIZE) - 1;

    int randomX = std::rand() % (maxX - 2) + 1;
    int randomY = std::rand() % (maxY - 2) + 1;

    return sf::Vector2f(randomX * BLOCK_SIZE, randomY * BLOCK_SIZE);
}

float Map::getBlockSize() const
{
    return BLOCK_SIZE;
}

int Map::getWidth() const
{
    return MAP_WIDTH;
}

int Map::getHeight() const
{
    return MAP_HEIGHT;
}