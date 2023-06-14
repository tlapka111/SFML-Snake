#include "game.h"

//private methods

void Game::processEvents(Snake &snake)
{
    while (this->window.pollEvent(this->event))
    {
        if (this->event.type == sf::Event::KeyPressed) 
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                snake.changeDirection(sf::Vector2f(MOVE_UP));
            } 
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                snake.changeDirection(sf::Vector2f(MOVE_DOWN));
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                snake.changeDirection(sf::Vector2f(MOVE_LEFT));
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                snake.changeDirection(sf::Vector2f(MOVE_RIGHT));
            }
        }

        if (event.type == sf::Event::Closed) window.close();    
    }
}

//public methods
Game::Game()
{
    this->window.create(sf::VideoMode(660, 660), "Snake", sf::Style::Close);
    this->window.setVerticalSyncEnabled(true);
    this->window.setFramerateLimit(60);
    this->texture.loadFromFile("images/board.png");   
    this->board.setTexture(this->texture);
}

Game::~Game()
{

}

void Game::Run(Snake &snake, Apple &apple)
{
    while (this->window.isOpen())
    {   
        processEvents(snake);
        if (snake.isAlive())
        {
            //this->timeSinceLastUpdate += this->clock.restart();
 
            //if (this->timeSinceLastUpdate >= this->TimePerFrame)
            {
                //this->timeSinceLastUpdate = sf::Time::Zero;
                //processEvents(snake);
                snake.moveSnakeBody(apple);
            }
        }
        render(snake, apple);
    }
}

void Game::render(Snake &snake, Apple &apple)
{
    this->window.clear(sf::Color(177, 205, 41));
    this->window.draw(this->board);
    this->window.draw(apple.drawApple());
    snake.drawSnakeShadowBody(this->window);
    snake.drawSnakeBody(this->window);
    this->window.display(); 
}