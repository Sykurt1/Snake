#include "Snake.h"

Snake::Snake(float blockSize, const sf::Vector2f& initialPosition)
        : blockSize(blockSize), direction(Direction::Right), isGrowing(false)
{
    segments.push_back({ initialPosition });
    updateOccupiedPositions();
}

void Snake::move() {
    updateBody();

    sf::Vector2f& head = segments[0].position;

    switch (direction) {
        case Direction::Up:
            head.y -= blockSize;
            break;
        case Direction::Down:
            head.y += blockSize;
            break;
        case Direction::Left:
            head.x -= blockSize;
            break;
        case Direction::Right:
            head.x += blockSize;
            break;
    }

    updateOccupiedPositions();
}

void Snake::setDirection(Direction newDirection) {
    // Blokada przed wcisnieciem "biegu wstecznego"
    if ((direction == Direction::Up && newDirection != Direction::Down) ||
        (direction == Direction::Down && newDirection != Direction::Up) ||
        (direction == Direction::Left && newDirection != Direction::Right) ||
        (direction == Direction::Right && newDirection != Direction::Left)) {
        direction = newDirection;
    }
}

void Snake::grow() {
    isGrowing = true;
}

bool Snake::isColliding(const sf::FloatRect& rect) const {
    for (size_t i = 1; i < segments.size(); ++i) {
        if (rect.intersects(sf::FloatRect(segments[i].position, sf::Vector2f(blockSize, blockSize)))) {
            return true;
        }
    }
    return false;
}

void Snake::draw(sf::RenderWindow& window) const {
    sf::RectangleShape bodyPart;
    bodyPart.setSize(sf::Vector2f(blockSize, blockSize));
    bodyPart.setFillColor(sf::Color::Green);
    for (const auto& segment : segments) {
        bodyPart.setPosition(segment.position);
        window.draw(bodyPart);
    }
}

sf::FloatRect Snake::getHeadBounds() const {
    return sf::FloatRect(segments[0].position, sf::Vector2f(blockSize, blockSize));
}

void Snake::updateBody() {
    if (isGrowing) {
        segments.push_back({ segments.back().position });
        isGrowing = false;
    }

    for (size_t i = segments.size() - 1; i > 0; --i) {
        segments[i].position = segments[i - 1].position;
    }
}

void Snake::updateOccupiedPositions() {
    occupiedPositions.clear();
    for (const auto& segment : segments) {
        occupiedPositions.insert(segment.position);
    }
}

float Snake::getBlockSize() const
{
    return blockSize;
}
