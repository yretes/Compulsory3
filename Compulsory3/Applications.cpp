#include "CompHeader.h"


void passcodeSet() {
    int passwordMoves = 0;
    int maxMoves = 9;
    char direction = 'x';
    char prevPassword[10];
    char inputPassword[10];
    int tries = 0;
    char passNum = 'y';
    struct Position {
        int x;
        int y;
    }pointer;
    std::vector<std::vector<char>>password{
        {'A','B','C','D'},
        {'E','F','G','H'},
        {'I','J','K','L'},
        {'M','N','O','P'}
    };

    std::fstream PassCode("Password.txt");
    for (int i = 0; i < 10; i++) {
        PassCode >> passNum;
        prevPassword[i] = passNum;
    }
    PassCode.close();

ATTEMPT:
    pointer.x = 0;
    pointer.y = 0;
    char passReset = 65;
    for (int i = 0; i < password.size(); i++) {
        for (int j = 0; j < password[i].size(); j++) {
            password[i][j] = passReset;
            passReset++;
        }
    }
    passwordMoves = 0;
    inputPassword[passwordMoves] = password[pointer.x][pointer.y];
    password[pointer.x][pointer.y] = '*';
    do {
        printf("\033c");

        for (int i = 0; i < password.size(); i++) {
            for (int j = 0; j < password[i].size(); j++) {
                std::cout << "|" << password[i][j];
            }
            std::cout << "|" << std::endl;
        }

        std::cout << "Use WASD to move the pointer, and input password." << std::endl;
    INPUT:
        direction = _getch();
        std::cout << direction;
        switch (direction) {
        case'w':case'W':
            if (pointer.x == 0) {
                std::cout << "\nImpossible input";
                goto INPUT;
            }
            else {
                pointer.x = pointer.x - 1;
            }
            break;
        case'a':case'A':
            if (pointer.y == 0) {
                std::cout << "\nImpossible input";
                goto INPUT;
            }
            else {
                pointer.y = pointer.y - 1;
            }
            break;
        case's':case'S':
            if (pointer.x == 3) {
                std::cout << "\nImpossible input";
                goto INPUT;
            }
            else {
                pointer.x = pointer.x + 1;
            }
            break;
        case'd':case'D':
            if (pointer.y == 3) {
                std::cout << "\nImpossible input";
                goto INPUT;
            }
            else {
                pointer.y = pointer.y + 1;
            }
            break;
        default:
            std::cout << "\nInvalid input";
            goto INPUT;
            break;
        }
        passwordMoves++;
        inputPassword[passwordMoves] = password[pointer.x][pointer.y];
        password[pointer.x][pointer.y] = '*';

    } while (passwordMoves < maxMoves);
    printf("\033c");
    if (sameCode(inputPassword, prevPassword) == true) {
        Beep(300, 200);

        std::cout << "You have entered your old password, password has not been changed";
        Sleep(2000);
        return;
    }
    if (sameCode(inputPassword, prevPassword) == false) {

        std::cout << "New password saved.";
        Beep(500, 200);
        Sleep(2000);
        std::fstream PassCode{ "Password.txt" };
        PassCode.clear();
        for (int i = 0; i < 10; i++) {
            passNum = inputPassword[i];
            PassCode << passNum;
        }
        PassCode.close();
        return;
    }

}

void passcodeInput() {
    int maxAttempts = 3;
    int passwordMoves = 0;
    int maxMoves = 9;
    char direction = 'x';
    char correctPassword[10];
    char inputPassword[10];
    int tries = 0;
    char passNum = 'y';
    struct Position {
        int x;
        int y;
    }pointer;
    std::vector<std::vector<char>>password{
        {'A','B','C','D'},
        {'E','F','G','H'},
        {'I','J','K','L'},
        {'M','N','O','P'}
    };

    std::fstream PassCode("Password.txt");
    for (int i = 0; i < 10; i++) {
        PassCode >> passNum;
        correctPassword[i] = passNum;
    }
    PassCode.close();

ATTEMPT:
    pointer.x = 0;
    pointer.y = 0;
    char passReset = 65;
    for (int i = 0; i < password.size(); i++) {
        for (int j = 0; j < password[i].size(); j++) {
            password[i][j] = passReset;
            passReset++;
        }
    }
    passwordMoves = 0;
    inputPassword[passwordMoves] = password[pointer.x][pointer.y];
    password[pointer.x][pointer.y] = '*';
    do {
        printf("\033c");

        for (int i = 0; i < password.size(); i++) {
            for (int j = 0; j < password[i].size(); j++) {
                std::cout << "|" << password[i][j];
            }
            std::cout << "|" << std::endl;
        }

        std::cout << "Use WASD to move the pointer, and input password." << std::endl;
    INPUT:
        direction = _getch();
        std::cout << direction;
        switch (direction) {
        case'w':case'W':
            if (pointer.x == 0) {
                std::cout << "\nImpossible input";
                goto INPUT;
            }
            else {
                pointer.x = pointer.x - 1;
            }
            break;
        case'a':case'A':
            if (pointer.y == 0) {
                std::cout << "\nImpossible input";
                goto INPUT;
            }
            else {
                pointer.y = pointer.y - 1;
            }
            break;
        case's':case'S':
            if (pointer.x == 3) {
                std::cout << "\nImpossible input";
                goto INPUT;
            }
            else {
                pointer.x = pointer.x + 1;
            }
            break;
        case'd':case'D':
            if (pointer.y == 3) {
                std::cout << "\nImpossible input";
                goto INPUT;
            }
            else {
                pointer.y = pointer.y + 1;
            }
            break;
        default:
            std::cout << "\nInvalid input";
            goto INPUT;
            break;
        }
        passwordMoves++;
        inputPassword[passwordMoves] = password[pointer.x][pointer.y];
        password[pointer.x][pointer.y] = '*';

    } while (passwordMoves < maxMoves);
    printf("\033c");
    if (sameCode(inputPassword, correctPassword) == false) {
        tries++;
        Beep(300, 200);
        if (tries == maxAttempts) {
            std::cout << "You have entered the wrong password too many times, exiting program. . .";
            exit(69);
        }
        std::cout << "Wrong Password";
        Sleep(2000);
        goto ATTEMPT;
    }
    if (sameCode(inputPassword, correctPassword) == true) {

        std::cout << "Correct password entered.";
        Beep(500, 200);
        Sleep(2000);
    }
}

bool sameCode(char input[], char fasit[]) {
    for (int i = 0; i < 10; i++) {
        if (input[i] != fasit[i]) {
            return false;
        }
    }
    return true;
}

char capitalize(char letter) {
    //simply capitalizes letters it recieves.
    return toupper(letter);
}


