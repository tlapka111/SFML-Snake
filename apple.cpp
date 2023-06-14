#include "apple.h"

//private methods
void Apple::generatePosition()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 20);
    this->x = distrib(gen) * 30;
    this->y = distrib(gen) * 30;
}

//public methods
Apple::Apple()
{
    generatePosition();
    this->texture.loadFromFile("images/apple.png");
    this->rectangle.setTexture(&texture);
    this->rectangle.setSize(sf::Vector2f(REC_SIZE, REC_SIZE));
    this->rectangle.setPosition(this->x, this->y);
}

Apple::~Apple()
{

}

void Apple::newSpawn(std::list<sf::RectangleShape> snakeBody)
{
    generatePosition();
    this->rectangle.setPosition(this->x, this->y);
    for (auto it = snakeBody.begin(); it != snakeBody.end(); it++)
    {
        if (this->rectangle.getPosition() == it->getPosition())
        {
            generatePosition();
            this->rectangle.setPosition(this->x, this->y);
            it = snakeBody.begin();
        }
    }
}

bool Apple::appleEaten(std::list<sf::RectangleShape> snakeHead)
{
    if (this->rectangle.getPosition() == snakeHead.begin()->getPosition()) return true;   
    return false;
}

sf::RectangleShape Apple::drawApple()
{
    return this->rectangle;
}