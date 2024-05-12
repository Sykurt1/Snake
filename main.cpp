#include "SnakeGame.h"
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Map map;
    sf::Vector2f initialPosition(map.getWidth() / 2.0f, map.getHeight() / 2.0f);
    Snake snake(map.getBlockSize(), initialPosition);

    SnakeGame game(map, snake);
    game.run();

    return 0;
}

