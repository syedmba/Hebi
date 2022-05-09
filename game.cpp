#include <iostream>
#include <string>

#include "game.h"

using namespace std;

struct Snake{
    int length;
    int speed;              // will not implement right now
    int **positionArray;
};

// void updatePositionArray() ???

string determineDirection(Snake snake){

}

void generateNextFrame(Snake snake ,string playerInput){
    if (playerInput == "UP"){

    } else if (playerInput == "DOWN"){

    } else if (playerInput == "LEFT"){
        
    } else if (playerInput == "RIGHT"){
        if (snake.positionArray[1][0] != snake.positionArray[0][0] + 1){    // if second part of body is not to right of head
            
        }
    } else {
        string direction = determineDirection(snake);
    }
}

bool Game(){
    Snake snake;
    snake.length = 2;
    snake.speed = 1;        // will not implement for now

    snake.positionArray = new int*[snake.length];
    for (int i = 0; i < snake.length; i++){
        snake.positionArray[i] = new int[2];
    }
    
}
