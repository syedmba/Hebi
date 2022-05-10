#include <iostream>
#include <string>
#include <ncurses.h>
#include <cmath>
#include <iomanip>
#include <unistd.h>

#include "game.h"

using namespace std;

// void updatePositionArray() ???

void printFrame(Snake snake){
    refresh();
    for (int i = 0; i < areaHeight; i++){
        for (int j = 0; j < areaLength; j++){
            if (i == areaHeight - 1 || i == 0 || j == 0 || j == areaLength - 1){
                mvprintw(areaHeight - i - 1, j, "X");
            } else {
                mvprintw(areaHeight - i - 1, j, " ");
            }
        }
    }
    for (int i = 0; i < snake.length; i++){
        mvprintw(areaHeight - 1 - snake.positionArray[i][1], snake.positionArray[i][0], "O");
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

void generateNextFrame(Snake snake, string playerInput){
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
    initscr();
    refresh();
    Snake snake;
    snake.length = 2;
    snake.speed = 1;        // will not implement for now

    int collectibleAt[2] = {-1, -1};

    int area[areaHeight][areaLength];

    snake.positionArray = new int*[snake.length];
    for (int i = 0; i < snake.length; i++){
        snake.positionArray[i] = new int[2];
        snake.positionArray[i][0] = 15 - i;
        snake.positionArray[i][1] = 15;
    }

    bool Alive = true;
    string playerInput;

    while (Alive){
        printFrame(snake);
        playerInput = takeInput();

        // set player input according to generateNextFrame() function
        // suggested implementation: change "UP" to "A" (etc) in the function and remove these lines
        if (playerInput == "A"){
            playerInput = "UP";
        } else if (playerInput == "B"){
            playerInput = "DOWN";
        } else if (playerInput == "C"){
            playerInput = "RIGHT";
        } else if (playerInput == "D"){
            playerInput = "LEFT";
        }

        generateCollectibles(snake, collectibleAt);
        generateNextFrame(snake, playerInput);
        // printFrame(snake);
    }

    return 1;
    
}

string takeInput(){
    move(areaHeight + 1, areaLength + 1);
    refresh();
    string response;
    response = getch();
    if (response != "\033"){
        takeInput();
    }
    getch();
    response = getch();
    if (response == "A" || response == "B" || response == "C" || response == "D"){
        return response;
    }
    return takeInput();
}

void generateCollectibles(Snake snake, int collectibleAt[2]){
    if (collectibleAt[0] == -1 && collectibleAt[1] == -1){
        srand(time(0));
        int determiner = rand() % 20;
        if (determiner != 3){
            return;
        } else {
            // proceed to generate new collectible
            int x_value = rand() % (areaLength - 1) + 1;
            int y_value = rand() % (areaHeight - 1) + 1;
            bool clash = false;
            for (int i = 0; i < snake.length; i++){
                if (x_value == snake.positionArray[i][0] && y_value == snake.positionArray[i][1]){
                    // clash with snake coordinates
                    clash = true;
                    break;
                }
            }
            while (clash){
                int x_value = rand() % (areaLength - 1) + 1;
                int y_value = rand() % (areaHeight - 1) + 1;
                for (int i = 0; i < snake.length; i++){
                    if (x_value == snake.positionArray[i][0] && y_value == snake.positionArray[i][1]){
                        // clash with snake coordinates
                        clash = true;
                        break;
                    }
                }
            }
            collectibleAt[0] = x_value;
            collectibleAt[1] = y_value;
        }
    }
    return;
}