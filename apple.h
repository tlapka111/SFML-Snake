#ifndef apple_h
#define apple_h

#define REC_SIZE 30.f

#include <SFML/Graphics.hpp>
#include <random>  
#include <list>

class Apple
{
private:
    sf::RectangleShape rectangle;
    sf::Texture texture;
    float x;
    float y;
    void generatePosition();
    
public:
    Apple();
    ~Apple();
    void newSpawn(std::list<sf::RectangleShape> snakeBody);
    bool appleEaten(std::list<sf::RectangleShape> snakeHead);
    sf::RectangleShape drawApple();
};

#endif