#include <iostream>
#include "CompHeader.h"
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <ctime>

int main()
{
    srand(time(nullptr));
    passcodeInput();
    menu();
}

void menu() {
    char option = 'x';
    bool playing = true;
    do {
        printf("\033c");
        std::cout << "\t[Main Menu]\n\n Please make a selection;";
        std::cout << "\n 1. Change password\n 2. Play Battleship\n 3. Quit";
        option = _getch();
        switch (option) {
        case '1':
            passcodeSet();
            break;
        case '2':
            playVsAI();
            break;
        case '3':
            playing = false;
            std::cout << "\n Exiting program . . .";
            break;
        default:
            std::cout << "\nInvalid selection";
            Sleep(1000);
            break;
        }
    } while (playing);
}

    
