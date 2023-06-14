CC=g++
CFLAGS=-std=c++17 -Wextra -Werror
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

snake:
	$(CC) $(CFLAGS) main.cpp snake.cpp apple.cpp game.cpp -o snake $(LFLAGS)