#include <iostream>
#include <string>
#include <ncurses.h>
#include <cmath>
#include <iomanip>
#include <unistd.h>

#include "game.h"

#define BLOCK   "\xE2\x96\x88"

using namespace std;



// void updatePositionArray() ???

void printFrame(Snake snake){
    initscr();
    for (int i = 0; i < areaHeight; i++){
        for (int j = 0; j < areaLength; j++){
            mvprintw(j, i, " ");
            if (i == areaHeight - 1 || i == 0 || j == 0 || j == areaLength - 1){
                mvprintw(j, i, BLOCK);
            }
        }
    }
    for (int i = 0; i < snake.length; i++){
        mvprintw(snake.positionArray[i][0], snake.positionArray[i][1], BLOCK);
    }
}

string determineDirection(Snake snake){
    int xhead = snake.positionArray[0][0];
    int yhead = snake.positionArray[0][1];
    int xsecond = snake.positionArray[1][0];
    int ysecond = snake.positionArray[1][1];
    if (xhead == xsecond + 1){
        return "RIGHT";
    } else if (xhead == xsecond - 1){
        return "LEFT";
    } else if (yhead == ysecond + 1){
        return "UP";
    } else {
        return "DOWN";
    }
}

void generateNextFrame(Snake snake ,string playerInput){
    string direction = determineDirection(snake);
    if (playerInput == "UP"){
        if (direction != "DOWN"){
            for (int i = snake.length - 1; i > 0; i--){
                snake.positionArray[i][0] = snake.positionArray[i-1][0];
                snake.positionArray[i][1] = snake.positionArray[i-1][1];
            }
            snake.positionArray[0][1] = snake.positionArray[0][1] + 1;
        }
    } else if (playerInput == "DOWN"){
        if (direction != "UP"){
            for (int i = snake.length - 1; i > 0; i--){
                snake.positionArray[i][0] = snake.positionArray[i-1][0];
                snake.positionArray[i][1] = snake.positionArray[i-1][1];
            }
            snake.positionArray[0][1] = snake.positionArray[0][1] - 1;
        }
    } else if (playerInput == "LEFT"){
        if (direction != "RIGHT"){
            for (int i = snake.length - 1; i > 0; i--){
                snake.positionArray[i][0] = snake.positionArray[i-1][0];
                snake.positionArray[i][1] = snake.positionArray[i-1][1];
            }
            snake.positionArray[0][0] = snake.positionArray[0][0] - 1;
        }
    } else if (playerInput == "RIGHT"){
        if (direction != "LEFT"){
            for (int i = snake.length - 1; i > 0; i--){
                snake.positionArray[i][0] = snake.positionArray[i-1][0];
                snake.positionArray[i][1] = snake.positionArray[i-1][1];
            }
            snake.positionArray[0][0] = snake.positionArray[0][0] + 1;
        }
    } else {
        generateNextFrame(snake, direction);
    }
}

bool Game(){
    Snake snake;
    snake.length = 2;
    snake.speed = 1;        // will not implement for now


    int area[areaHeight][areaLength];

    snake.positionArray = new int*[snake.length];
    for (int i = 0; i < snake.length; i++){
        snake.positionArray[i] = new int[2];
    }

    bool Alive = true;
    string playerInput;

    while (Alive){
        playerInput = takeInput();
        generateNextFrame(snake, playerInput);
        printFrame(snake);
    }

    return 1;
    
}

string takeInput(){
    string response;
    response = getch();
    if (response != "^["){
        takeInput();
    }
    getch();
    response = getch();
    if (response == "A" || response == "B" || response == "C" || response == "D"){
        return response;
    }
    return takeInput();
}
