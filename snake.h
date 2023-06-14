#ifndef snake_h
#define snake_h

#include <list>
#include "apple.h"

#define REC_SIZE 30.f
#define MOVE_UP 0.f, -1.f
#define MOVE_DOWN 0.f, 1.f
#define MOVE_LEFT -1.f, 0.f
#define MOVE_RIGHT 1.f, 0.f
#define MAX_BOUND_X 600.f
#define MAX_BOUND_Y 600.f
#define MIN_BOUND_X 30.f
#define MIN_BOUND_Y 30.f

class Snake
{
private:
    std::list<sf::RectangleShape> body;
    std::list<sf::RectangleShape> shadowBody;
    std::list<sf::Vector2f> direction;
    sf::Vector2f nextPosition;
    sf::Vector2f actualPosition;
    int counter;
    float snakeSpeed;
    bool alive;
    bool addDirection;
    sf::RectangleShape createRectangle(float pos_x, float pos_y);
    void addNewBody();
    bool checkCollision();
    void nextDirection();
    bool validDirection();
    void stopSnake();

public:
    Snake();
    ~Snake();
    void moveSnakeBody(Apple &apple);
    void changeDirection(sf::Vector2f vector);
    bool isAlive();
    void drawSnakeBody(sf::RenderWindow &window);
    void drawSnakeShadowBody(sf::RenderWindow &window);
};

#endif