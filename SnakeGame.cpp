#include "SnakeGame.h"

SnakeGame::SnakeGame(Map& map, Snake& snake)
        : window(sf::VideoMode(map.getWidth(), map.getHeight()), "SFML Snake Game"),
          map(map),
          snake(snake),
          blockSize(snake.getBlockSize()), isGameOver(false)
{
    sf::Vector2f initialPosition(map.getWidth() / 2.0f, map.getHeight() / 2.0f);
    snake = Snake(blockSize, initialPosition);

    apple.setPosition(sf::Vector2f(10 * blockSize, 10 * blockSize));
    apple.setSize(sf::Vector2f(blockSize, blockSize));
    apple.setFillColor(sf::Color::Red);

    font.loadFromFile("../ARIBL0,ttf");
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(map.getWidth() / 2.0f - 120, map.getHeight() / 2.0f - 20);

    restartText.setFont(font);
    restartText.setCharacterSize(20);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(map.getWidth()/ 2.0f - 130, map.getHeight()/ 2.0f + 20);

}

void SnakeGame::run() {
    sf::Clock clock;
    sf::Time elapsed = sf::Time::Zero;
    const sf::Time frameTime = sf::seconds(1.0f / 10.0f); // 10 FPS

    while (window.isOpen()) {
        processEvents();
        elapsed += clock.restart();

        while (elapsed >= frameTime) {
            elapsed -= frameTime;
            processEvents();
            update();
        }

        render();
    }
}

void SnakeGame::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (!isGameOver) {
                if (event.key.code == sf::Keyboard::Up) {
                    snake.setDirection(Direction::Up);
                } else if (event.key.code == sf::Keyboard::Down) {
                    snake.setDirection(Direction::Down);
                } else if (event.key.code == sf::Keyboard::Left) {
                    snake.setDirection(Direction::Left);
                } else if (event.key.code == sf::Keyboard::Right) {
                    snake.setDirection(Direction::Right);
                }
            } else {
                if (event.key.code == sf::Keyboard::Enter) {
                    restartGame();
                }
            }
        }
    }
}

void SnakeGame::update() {
    if (isGameOver) {
        return;
    }

    snake.move();

    sf::FloatRect appleBounds = apple.getGlobalBounds();
    sf::FloatRect headBounds = snake.getHeadBounds();

    if (headBounds.intersects(appleBounds)) {
        snake.grow();
        apple.setPosition(map.generateRandomPosition());
    }

    if (map.isColliding(snake.getHeadBounds()) || snake.isColliding(snake.getHeadBounds())) {
        isGameOver = true;
    }
}

void SnakeGame::render() {
    window.clear(sf::Color::Black);

    map.draw(window);
    snake.draw(window);
    window.draw(apple);

    if (isGameOver) {
        if (font.loadFromFile("../ARIBL0.ttf")) {

            window.draw(gameOverText);

            window.draw(restartText);
        }
    }
    window.display();
}

void SnakeGame::restartGame()
{
    isGameOver = false;
    snake = Snake(map.getBlockSize(), sf::Vector2f(map.getWidth() / 2.0f, map.getHeight() / 2.0f));
    apple.setPosition(map.generateRandomPosition());
}