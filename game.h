//game.h

#ifndef GAME
#define GAME

#include <ncurses.h>

struct Snake{
    int length;
    int speed;              // will not implement right now
    int **positionArray;
};

const int areaHeight = 30;
const int areaLength = 50;

bool Game();
std::string determineDirection(Snake snake);
void generateNextFrame(Snake snake ,std::string playerInput);
std::string takeInput();
void printFrame(Snake snake);

#endif

