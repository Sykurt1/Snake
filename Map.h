#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H


#include <SFML/Graphics.hpp>

class Map {
public:
    Map();
    void draw(sf::RenderWindow& window) const; // render granic
    bool isColliding(const sf::FloatRect& rect) const; // kolizja granic
    float getBlockSize() const; // getter rozmiaru granic
    int getWidth() const; // getter szerokosci
    int getHeight() const; // getter wysokosci
    sf::Vector2f generateRandomPosition() const; // generator pozycji do polozenia jablka na planszy

private:
    int MAP_WIDTH = 800;
    int MAP_HEIGHT = 600;
    float BLOCK_SIZE = 20.0f;
    sf::RectangleShape boundaries[4];
};

#endif //SNAKE_MAP_H
