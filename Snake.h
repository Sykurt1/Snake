#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <vector>
#include <functional>

namespace std {     //probujac rozwiazac problem z funkcja update occupied positions znalzalem rozwiazanie i trzeba bylo zaimplementowac cos takiego
    template <>
    struct hash<sf::Vector2f> {
        std::size_t operator()(const sf::Vector2f& vector) const {
            std::size_t h1 = std::hash<float>{}(vector.x);
            std::size_t h2 = std::hash<float>{}(vector.y);
            return h1 ^ (h2 << 1);
        }
    };
}

enum class Direction { Up, Down, Left, Right };

struct SnakeSegment {
    sf::Vector2f position;
};

class Snake {
    std::vector<SnakeSegment> segments;
    std::unordered_set<sf::Vector2f> occupiedPositions;
    float blockSize;
    Direction direction;
    bool isGrowing;
public:
    Snake(float blockSize, const sf::Vector2f& initialPosition); // konstruktor weza ustawiajacy jego rozmiar i pozycje startowa
    void move();  //funkcja poruszajaca wezem zaleznie od obecnie nadanego kierunku za pomoca strzalek
    void setDirection(Direction newDirection); // funkcja ustawiajaca aktualny kierunek
    void grow(); // funkcja aktualizujaca rozmiar weza po zjedzeniu jablka
    bool isColliding(const sf::FloatRect& rect) const; // funkcja sprawdzajaca kolizje
    void draw(sf::RenderWindow& window) const; // funkcja rysujaca segmenty weza
    sf::FloatRect getHeadBounds() const; // getter granic glowy
    float getBlockSize()const; // getter rozmiaru bloku weza
    void updateBody(); // funkcja aktualizujaca polozenie weza i aktualizacje rozmiaru
    void updateOccupiedPositions(); // funkcja aktualizujaca zajmowane przez weza pozycje, sluzy do detekcji kolizji ze swoim ogonem.
};
