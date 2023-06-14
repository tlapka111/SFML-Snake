#include "snake.h"

//private methods

sf::RectangleShape Snake::createRectangle(float pos_x, float pos_y)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(REC_SIZE, REC_SIZE));
    rectangle.setPosition(pos_x, pos_y);
    rectangle.setFillColor(sf::Color::Black);
    return rectangle;
}

void Snake::addNewBody()
{
    sf::Vector2f position = this->body.back().getPosition();
    this->shadowBody.push_back(createRectangle(position.x, position.y));
    //float x = position.x - (this->direction.back().x * REC_SIZE);
    //float y = position.y - (this->direction.back().y * REC_SIZE);
    this->body.push_back(createRectangle(position.x, position.y));
    
    //this->direction.push_back(this->direction.back());
}

bool Snake::checkCollision()
{
    sf::Vector2f headPosition = this->body.begin()->getPosition();
    auto it = this->body.begin();
    it++;
    //body collision
    for (it; it != this->body.end(); it++)
    {
        if (headPosition == it->getPosition()) return true;
    }

    //wall collision, if next step would cross border -> crash
    if (headPosition.x + (this->direction.front().x * this->snakeSpeed) < MIN_BOUND_X) return true;
    else if (headPosition.x + (this->direction.front().x * this->snakeSpeed) > MAX_BOUND_X) return true;
    else if (headPosition.y + (this->direction.front().y * this->snakeSpeed) < MIN_BOUND_Y) return true;
    else if (headPosition.y + (this->direction.front().y * this->snakeSpeed) > MAX_BOUND_Y) return true;
    
    return false;
}

void Snake::nextDirection()
{
    if (validDirection())
    {
        this->direction.push_front(this->actualPosition);
    }
    else
    {
        this->direction.push_front(this->nextPosition);
        this->actualPosition = this->nextPosition;
        
    }
    this->direction.pop_back();
}

bool Snake::validDirection()
{
    bool valid = false;

    valid = valid || (this->actualPosition == sf::Vector2f(MOVE_UP) && this->nextPosition == sf::Vector2f(MOVE_DOWN));
    valid = valid || (this->actualPosition == sf::Vector2f(MOVE_LEFT) && this->nextPosition == sf::Vector2f(MOVE_RIGHT));
    valid = valid || (this->actualPosition == sf::Vector2f(MOVE_DOWN) && this->nextPosition == sf::Vector2f(MOVE_UP));
    valid = valid || (this->actualPosition == sf::Vector2f(MOVE_RIGHT) && this->nextPosition == sf::Vector2f(MOVE_LEFT));

    return valid;
}

void Snake::stopSnake()
{
    for (auto it = this->direction.begin(); it != this->direction.end(); it++)
    {
        *it = sf::Vector2f(0, 0);
    }
    this->body.begin()->setFillColor(sf::Color::Red);
    this->actualPosition = sf::Vector2f(0,0);
    this->nextPosition = sf::Vector2f(0,0);
    this->alive = false;
}

//public methods
Snake::Snake()
{
    //starting cord
    int x = 300;
    int y = 300;

    for (int i = 0; i < 4; i++)
    {
        if (i < 3) this->shadowBody.push_back(createRectangle(x, y));

        this->body.push_back(createRectangle(x, y));
        this->direction.push_back(sf::Vector2f(MOVE_RIGHT));
        x = x - REC_SIZE;       
    }

    this->actualPosition = sf::Vector2f(MOVE_RIGHT);
    this->nextPosition = sf::Vector2f(MOVE_RIGHT);
    this->snakeSpeed = 3.f;
    this->counter = 1;
    this->alive = true;
    this->addDirection = false;
}

Snake::~Snake()
{

}

void Snake::moveSnakeBody(Apple &apple)
{
    //move each frame
    auto itt = this->direction.begin();

    for (auto it = this->body.begin(); it != this->body.end(); it++)
    {
        it->move((*itt) * this->snakeSpeed);  
        itt++;
    }
    //change direction every nth frame
    if (this->counter == REC_SIZE/this->snakeSpeed)
    {
        if (this->addDirection)
        {
            this->direction.push_back(this->direction.back());
            this->addDirection = false;
        }
        
        //shadow snake movement by squares
        itt = this->direction.begin();
        for (auto it = this->shadowBody.begin(); it != this->shadowBody.end(); it++)
        {
            it->move(*itt * REC_SIZE);
            itt++;
        }

        if (apple.appleEaten(this->body)) 
        {
            addNewBody();
            this->addDirection = true;
            apple.newSpawn(this->body);
        }
        nextDirection();
        if (checkCollision()) stopSnake();

        this->counter = 0;
    }

    this->counter++;
}

void Snake::changeDirection(sf::Vector2f newPosition)
{
    this->nextPosition = newPosition;
}

bool Snake::isAlive()
{
    return this->alive;
}

void Snake::drawSnakeBody(sf::RenderWindow &window)
{
    for (auto it = this->body.rbegin(); it != this->body.rend(); it++)
    {
        window.draw(*it);
    }
}

void Snake::drawSnakeShadowBody(sf::RenderWindow &window)
{
    for (auto it = this->shadowBody.begin(); it != this->shadowBody.end(); it++)
    {
        window.draw(*it);
    }
}