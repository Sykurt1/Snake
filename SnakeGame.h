#pragma once

#include "Map.h"
#include "Snake.h"

class SnakeGame {
    sf::RenderWindow window;
    Map& map;
    Snake& snake;
    sf::RectangleShape apple;
    float blockSize;
    bool isGameOver;
    sf::Text gameOverText, restartText;
    sf::Font font;
public:
    SnakeGame(Map& map, Snake& snake); //konstruktor otrzymujacy referencje na mape i weza
    void restartGame(); // funkcja do restartowania gry po jej zakonczeniu
    void run(); //funkcja odpowiedzialna za dzialanie gry
    void processEvents(); //funkcja zbierajaca wejscie z klawiatury i na jego podstawie poruszajaca wezem
    void update(); // funkcja aktualizujaca polozenie weza i uwzgledniajaca kolizje z jablkiem oraz murem
    void render(); // funkcja wyswietlajaca obraz (u mnie nierozwiazany problem z zaladowaniem czcionki (failed to create the font face) ;(((
    //powinien byc komunikat o ponownym rozpoczeciu gry po kliknieciu przycisku enter (dziala)
};