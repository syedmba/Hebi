//game.h

#ifndef GAME
#define GAME

#include <ncurses.h>

#define BLOCK   "\xE2\x96\x88"
// "\u2588"

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
void generateCollectibles(Snake snake, int collectibleAt[2]);

#endif

