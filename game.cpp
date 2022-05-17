#include <iostream>
#include <string>
#include <ncurses.h>
#include <cmath>
#include <iomanip>
#include <unistd.h>
#include <vector>

#include "game.h"

using namespace std;

// void updatePositionArray() ???

void printFrame(Snake snake, int collectibleAt[2]){
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
        mvprintw(areaHeight - 1 - snake.positionArray[i].y, snake.positionArray[i].x, "O");
    }
    if (collectibleAt[0] != 1 && collectibleAt[1] != 1){
        mvprintw(areaHeight - 1 - collectibleAt[1], collectibleAt[0], "+");
    }
    
}

string determineDirection(Snake snake){
    int xhead = snake.positionArray[0].x;
    int yhead = snake.positionArray[0].y;
    int xsecond = snake.positionArray[1].x;
    int ysecond = snake.positionArray[1].y;
    if (xhead == xsecond + 1){
        return "RIGHT";
    } else if (xhead == xsecond - 1){
        return "LEFT";
    } else if (yhead == ysecond + 1){
        return "UP";
    } else {
        return "DOWN";
    }
    return "NONE";
}

void makeSnakeLonger(Snake &snake, int collectibleAt[2]){
    // preserve old coordinates
    vector<Coords> oldSnake;
    for (int i = 0; i < snake.length; i++){
        oldSnake.push_back(snake.positionArray[i]);
    }
    // int **oldSnake;
    // oldSnake = new int*[snake.length];
    // for (int i = 0; i < snake.length; i++){
    //     oldSnake[i] = new int[2];
    //     oldSnake[i][0] = snake.positionArray[i].x;
    //     oldSnake[i][1] = snake.positionArray[i].y;
    // }
    // delete [] snake.positionArray;
    // create new array
    snake.length++;

    snake.positionArray.clear();
    Coords collectibleCoords;
    collectibleCoords.x = collectibleAt[0];
    collectibleCoords.y = collectibleAt[1];
    snake.positionArray.push_back(collectibleCoords);
    for (int i = 0; i < snake.length - 1; i++){
        snake.positionArray.push_back(oldSnake[i]);
    }
    oldSnake.clear();
    // snake.positionArray = new int*[snake.length];
    // snake.positionArray[0][0] = collectibleAt[0];
    // snake.positionArray[0][1] = collectibleAt[1];
    // for (int i = 1; i < snake.length; i++){
        // snake.positionArray[i][0] = oldSnake[i-1][0];
        // snake.positionArray[i][1] = oldSnake[i-1][1];
    // }
    collectibleAt[0] = -1;
    collectibleAt[1] = -1;
}

void generateNextFrame(Snake &snake, string playerInput, int collectibleAt[2]){
    string direction = determineDirection(snake);
    if (playerInput == "UP"){
        if (direction != "DOWN"){
            if (snake.positionArray[0].x == collectibleAt[0] && snake.positionArray[0].y == collectibleAt[1]){
                // collectible will be collected
                makeSnakeLonger(snake, collectibleAt);
            }
            for (int i = snake.length - 1; i > 0; i--){
                snake.positionArray[i].x = snake.positionArray[i-1].x;
                snake.positionArray[i].y = snake.positionArray[i-1].y;
            }
            snake.positionArray[0].y = snake.positionArray[0].y + 1;
        }
    } else if (playerInput == "DOWN"){
        if (direction != "UP"){
            if (snake.positionArray[0].x == collectibleAt[0] && snake.positionArray[0].y == collectibleAt[1]){
                // collectible will be collected
                makeSnakeLonger(snake, collectibleAt);
            }
            for (int i = snake.length - 1; i > 0; i--){
                snake.positionArray[i].x = snake.positionArray[i-1].x;
                snake.positionArray[i].y = snake.positionArray[i-1].y;
            }
            snake.positionArray[0].y = snake.positionArray[0].y - 1;
        }
    } else if (playerInput == "LEFT"){
        if (direction != "RIGHT"){
            if (snake.positionArray[0].x == collectibleAt[0] && snake.positionArray[0].y == collectibleAt[1]){
                // collectible will be collected
                makeSnakeLonger(snake, collectibleAt);
            }
            for (int i = snake.length - 1; i > 0; i--){
                snake.positionArray[i].x = snake.positionArray[i-1].x;
                snake.positionArray[i].y = snake.positionArray[i-1].y;
            }
            snake.positionArray[0].x = snake.positionArray[0].x - 1;
        }
    } else if (playerInput == "RIGHT"){
        if (direction != "LEFT"){
            if (snake.positionArray[0].x == collectibleAt[0] && snake.positionArray[0].y == collectibleAt[1]){
                // collectible will be collected
                makeSnakeLonger(snake, collectibleAt);
            }
            for (int i = snake.length - 1; i > 0; i--){
                snake.positionArray[i].x = snake.positionArray[i-1].x;
                snake.positionArray[i].y = snake.positionArray[i-1].y;
            }
            snake.positionArray[0].x = snake.positionArray[0].x + 1;
        }
    } else {
        generateNextFrame(snake, direction, collectibleAt);
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

    for (int i = 0; i < snake.length; i++){
        Coords thisCoords;
        thisCoords.x = 15 - i;
        thisCoords.y = 15;
        snake.positionArray.push_back(thisCoords);
    }


    // snake.positionArray = new int*[snake.length];
    // for (int i = 0; i < snake.length; i++){
    //     snake.positionArray[i] = new int[2];
    //     snake.positionArray[i][0] = 15 - i;
    //     snake.positionArray[i][1] = 15;
    // }

    bool Alive = true;
    string playerInput;

    while (Alive){
        printFrame(snake, collectibleAt);
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
        generateNextFrame(snake, playerInput, collectibleAt);
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
        srand(time(NULL));
        int determiner = 3;
        if (determiner != 3){
            return;
        } else {
            // proceed to generate new collectible
            int x_value = rand() % (areaLength - 1) + 1;
            int y_value = rand() % (areaHeight - 1) + 1;
            bool clash = false;
            for (int i = 0; i < snake.length; i++){
                if (x_value == snake.positionArray[i].x && y_value == snake.positionArray[i].y){
                    // clash with snake coordinates
                    clash = true;
                    break;
                }
            }
            while (clash){
                clash = false;
                int x_value = rand() % (areaLength - 1) + 1;
                int y_value = rand() % (areaHeight - 1) + 1;
                for (int i = 0; i < snake.length; i++){
                    if (x_value == snake.positionArray[i].x && y_value == snake.positionArray[i].y){
                        // clash with snake coordinates
                        clash = true;
                        break;
                    }
                }
            }
            collectibleAt[0] = x_value;
            collectibleAt[1] = y_value;
            cout << "(" << collectibleAt[0] << ", " << collectibleAt[1] << ")" << endl;
        }
    }
    return;
}