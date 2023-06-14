#ifndef game_h
#define game_h

#include "snake.h"
#include "apple.h"

class Game
{
private:
    sf::RenderWindow window;
    sf::Event event;
    sf::Texture texture;
    sf::Sprite board;
    void processEvents(Snake &snake);
    void render(Snake &snake, Apple &apple);
public:
    Game();
    ~Game();
    void Run(Snake &snake, Apple &apple);
};

#endif