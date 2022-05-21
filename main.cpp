#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

#include "game.h"


int main(){

    cout << "Starting Game ..." << endl;

    // sleep(5);

    // game title

    const int titleSize = 10;
    string title_array[titleSize] = {
        "   ██░ ██ ▓█████  ▄▄▄▄    ██▓",
        "  ▓██░ ██▒▓█   ▀ ▓█████▄ ▓██▒",
        "  ▒██▀▀██░▒███   ▒██▒ ▄██▒██▒",
        "  ░▓█ ░██ ▒▓█  ▄ ▒██░█▀  ░██░",
        "  ░▓█▒░██▓░▒████▒░▓█  ▀█▓░██░",
        "   ▒ ░░▒░▒░░ ▒░ ░░▒▓███▀▒░▓  ",
        "   ▒ ░▒░ ░ ░ ░  ░▒░▒   ░  ▒ ░",
        "   ░  ░░ ░   ░    ░    ░  ▒ ░",
        "   ░  ░  ░   ░  ░ ░       ░  ",
        "                       ░     "
    };

    for (int i = 0; i < titleSize; i++){
        cout << title_array[i] << endl;
        // sleep(1);
    }

    // cout << "   ██░ ██ ▓█████  ▄▄▄▄    ██▓" << endl;
    // cout << "  ▓██░ ██▒▓█   ▀ ▓█████▄ ▓██▒" << endl;
    // cout << "  ▒██▀▀██░▒███   ▒██▒ ▄██▒██▒" << endl;
    // cout << "  ░▓█ ░██ ▒▓█  ▄ ▒██░█▀  ░██░" << endl;
    // cout << "  ░▓█▒░██▓░▒████▒░▓█  ▀█▓░██░" << endl;
    // cout << "   ▒ ░░▒░▒░░ ▒░ ░░▒▓███▀▒░▓  " << endl;
    // cout << "   ▒ ░▒░ ░ ░ ░  ░▒░▒   ░  ▒ ░" << endl;
    // cout << "   ░  ░░ ░   ░    ░    ░  ▒ ░" << endl;
    // cout << "   ░  ░  ░   ░  ░ ░       ░  " << endl;
    // cout << "                       ░     " << endl;

    // sleep(3);

    // run actual game

    int result = Game();

    return result;
}

