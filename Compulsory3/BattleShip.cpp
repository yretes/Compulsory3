#include "CompHeader.h"

const int m = 6;
const int n = 6;
const char BLANK = ' ';
const char SHIP = 'S';
const char MISS = 'M';
const char HIT = 'H';
int numberOfHits = 0;
int numberOfShots = m*n;
char board[m][n];
char AIboard[m][n];
int turnsSinceHit = 0;
int lastRow = 0;
int lastColumn = 0;

//std::string splash = "splashJumpinga.wav";

int letterToNumber(char letter) {
    return static_cast<int>(letter) - 65;
}

char numberToLetter(int number) {
    return static_cast<char>(number) + 65;
}

void bsLogo() {
    printf("\033c");
    std::cout << "______       _   _   _           _     _       ";
    std::cout << "\n| ___ \\     | | | | | |         | |   (_)      ";
    std::cout << "\n| |_/ / __ _| |_| |_| | ___  ___| |__  _ _ __  ";
    std::cout << "\n| ___ \\/ _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\ ";
    std::cout << "\n| |_/ / (_| | |_| |_| |  __/\\__ \\ | | | | |_) |";
    std::cout << "\n\\____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/ ";
    std::cout << "\n                                        | |    ";
    std::cout << "\n                                        |_|";
    std::cout << "\n\n \tPress any key to play!";
    _getch();
}

void makeEmptyBoard() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = BLANK;
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            AIboard[i][j] = BLANK;
        }
    }

}

int randomRow() {
    return (rand() % m);
}

int randomColumn() {
    return (rand() % n );
}

void writeLetters() {
    char letter = 'A';
    std::cout << "  ";
    for (int i = 0; i < n; i++) {
        std::cout << letter<<" ";
        letter++;
    }
    std::cout << "\n\n";
}

void makeBoard(int numberOfShips) {
    int shipM = 0;
    int shipN = 0;
    for (int i = 0; i < numberOfShips; i++) {
        do {
            shipM = randomRow();
            shipN = randomColumn();
        } while (board[shipM][shipN] == SHIP);
        board[shipM][shipN] = SHIP;
    }
}

void makeBoard3(int numberOfShips) {
    int shipM = 0;
    int shipN = 0;
    bool vertical = true;
    int boatNo = 1;
    for (int i = 0; i < numberOfShips; i++) {
        vertical = isVerticalRNG();
        if (vertical == true) {
            REROLLVERTICAL:
                shipM = randomRow();
                shipN = randomColumn();
                if (shipM <= 0 || shipM+1>=m) {
                    goto REROLLVERTICAL;
                }
                if (board[shipM][shipN] == SHIP || board[shipM + 1][shipN] == SHIP || board[shipM - 1][shipN] == SHIP)
                    goto REROLLVERTICAL;
            board[shipM][shipN] = SHIP;
            board[shipM+1][shipN] = SHIP;
            board[shipM-1][shipN] = SHIP;
        }
        if (vertical == false) {
            REROLLHORIZONTAL:
                shipM = randomRow();
                shipN = randomColumn();
                if (shipN <= 0 || shipN+1 >= n) {
                    goto REROLLHORIZONTAL;
                }
                if (board[shipM][shipN] == SHIP || board[shipM][shipN + 1] == SHIP || board[shipM][shipN - 1] == SHIP)
                    goto REROLLHORIZONTAL;
            board[shipM][shipN] = SHIP;
            board[shipM][shipN+1] = SHIP;
            board[shipM][shipN-1] = SHIP;
        }
    }
    std::cout << std::endl;
}

void AImakeBoard3(int numberOfShips) {
    int shipM = 0;
    int shipN = 0;
    bool vertical = true;
    for (int i = 0; i < numberOfShips; i++) {
        vertical = isVerticalRNG();
        if (vertical == true) {
        REROLLVERTICAL:
            shipM = randomRow();
            shipN = randomColumn();
            if (shipM <= 0 || shipM + 1 >= m) {
                goto REROLLVERTICAL;
            }
            if (AIboard[shipM][shipN] == SHIP || AIboard[shipM + 1][shipN] == SHIP || AIboard[shipM - 1][shipN] == SHIP)
                goto REROLLVERTICAL;
            AIboard[shipM][shipN] = SHIP;
            AIboard[shipM + 1][shipN] = SHIP;
            AIboard[shipM - 1][shipN] = SHIP;
        }
        if (vertical == false) {
        REROLLHORIZONTAL:
            shipM = randomRow();
            shipN = randomColumn();
            if (shipN <= 0 || shipN + 1 >= n) {
                goto REROLLHORIZONTAL;
            }
            if (AIboard[shipM][shipN] == SHIP || AIboard[shipM][shipN + 1] == SHIP || AIboard[shipM][shipN - 1] == SHIP)
                goto REROLLHORIZONTAL;
            AIboard[shipM][shipN] = SHIP;
            AIboard[shipM][shipN + 1] = SHIP;
            AIboard[shipM][shipN - 1] = SHIP;
        }
    }
    std::cout << std::endl;
}

bool isVerticalRNG() {
    int result = 0;
    result =rand() % 2;
    if (result == 1)
        return 1;
    else if (result == 0)
        return 0;
}

void printBoard() {
    int boardNum = 1;
    std::cout << " [Your board]" << std::endl;
    for (int i = 0; i < m; i++) {
        std::cout << boardNum;
        for (int j = 0; j < n; j++) {
            std::cout <<"|"<< board[i][j];
        }
        std::cout <<"|"<< std::endl;
        boardNum++;
    }
}

void printPlayerBoard() {
    int boardNum = 1;
    for (int i = 0; i < m; i++) {
        std::cout << boardNum;
        for (int j = 0; j < n; j++) {
            std::cout << "|";
            if (board[i][j] == SHIP) {
                std::cout << BLANK;
            }
            else {
                std::cout << board[i][j];
            }
        }
        std::cout <<"|"<< std::endl;
        boardNum++;
    }
}

void AIprintBoard() {
    int boardNum = 1;
    std::cout << " [Opponent board]"<<std::endl;
    for (int i = 0; i < m; i++) {
        std::cout << boardNum;
        for (int j = 0; j < n; j++) {
            std::cout << "|";
            if (AIboard[i][j] == SHIP) {
                std::cout << BLANK;
            }
            else {
                std::cout << AIboard[i][j];
            }
        }
        std::cout << "|" << std::endl;
        boardNum++;
    }
}

void shoot() {
    int inputRow = 0;
    char inputColumn = 'x';
    int columnActual = 0;
    std::cout << "\n We have [" << numberOfShots << "] Shots left, Captain!\n Where would you like us to fire?" << std::endl;
    std::cout << " Fire at: ";
    std::cin >> inputColumn >> inputRow;
    inputColumn= capitalize(inputColumn);
    inputRow = inputRow - 1;
    while (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Invalid input!\n Input column first, then row (letter + number): ";
            std::cin >> inputColumn >> inputRow;
            inputColumn = capitalize(inputColumn);
            inputRow = inputRow - 1;
    }
    while (inputColumn <'A' || inputColumn > n + 64 || inputRow< 0 || inputRow > m) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Invalid input!\n Your input must be withing the boards parameters! : ";
            std::cin >> inputColumn >> inputRow;
            inputColumn = capitalize(inputColumn);
            inputRow = inputRow - 1;
    }
    columnActual = letterToNumber(inputColumn);
    if (board[inputRow][columnActual] == SHIP) {
        board[inputRow][columnActual] = HIT;
        numberOfHits++;
    }
    else if(board[inputRow][columnActual] == BLANK)
        board[inputRow][columnActual] = MISS;
    numberOfShots = numberOfShots - 1;
}

void shootAtAI() {
    int inputRow = 0;
    char inputColumn = 'x';
    int columnActual = 0;
    std::cout << "\n We have [" << numberOfShots << "] Shots left, Captain!\n Where would you like us to fire?" << std::endl;
    std::cout << " Fire at: ";
    std::cin >> inputColumn >> inputRow;
    inputColumn = capitalize(inputColumn);
    inputRow = inputRow - 1;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Invalid input!\n Input column first, then row (letter + number): ";
        std::cin >> inputColumn >> inputRow;
        inputColumn = capitalize(inputColumn);
        inputRow = inputRow - 1;
    }
    while (inputColumn <'A' || inputColumn > n + 64 || inputRow< 0 || inputRow > m) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Invalid input!\n Your input must be withing the boards parameters! : ";
        std::cin >> inputColumn >> inputRow;
        inputColumn = capitalize(inputColumn);
        inputRow = inputRow - 1;
    }
    columnActual = letterToNumber(inputColumn);
    if (AIboard[inputRow][columnActual] == SHIP) {
        AIboard[inputRow][columnActual] = HIT;
        numberOfHits++;
    }
    else if (AIboard[inputRow][columnActual] == BLANK)
        AIboard[inputRow][columnActual] = MISS;
    numberOfShots = numberOfShots - 1;
}

void AIshoot() {
    int inputRow = 0;
    int columnActual = 0;
    std::cout << "Captain Artificial Michael is thinking. . ."<<std::endl;
    Sleep(2000);
PRECISION:
    if (turnsSinceHit < 4) {
    
        if (turnsSinceHit == 0) {
            inputRow = lastRow + 1;
            columnActual = lastColumn;
        }
        else if (turnsSinceHit == 1) {
            inputRow = lastRow - 1;
            columnActual = lastColumn;
        }
        else if (turnsSinceHit == 2) {
            inputRow = lastRow;
            columnActual = lastColumn+1;
        }
        else if (turnsSinceHit == 3) {
            inputRow = lastRow;
            columnActual = lastColumn-1;
        }
        if (inputRow<0 || inputRow>=m || columnActual<0 || columnActual>=n) {
            turnsSinceHit++;
            goto PRECISION;
        }
        if (board[inputRow][columnActual] == HIT){
            turnsSinceHit++;
            goto PRECISION;
        }
        if (board[inputRow][columnActual] == MISS) {
            turnsSinceHit++;
            goto PRECISION;
        }
        

    }
    else {
    RETARGET:
        inputRow = randomRow();
        columnActual = randomColumn();
        if (board[inputRow][columnActual] == HIT||board[inputRow][columnActual]==MISS)
            goto RETARGET;
    }
    if (board[inputRow][columnActual] == SHIP) {
        board[inputRow][columnActual] = HIT;
        turnsSinceHit = 0;
        lastColumn = columnActual;
        lastRow = inputRow;
    }
    else if (board[inputRow][columnActual] == BLANK) {
        board[inputRow][columnActual] = MISS;
        turnsSinceHit++;
    }
    std::cout << " Captain Artificial Michael fires at "<<numberToLetter(columnActual)<<inputRow+1<<"!"<<std::endl;
    Sleep(1000);
}

void play() {
    int numberOfShips = 3;
    int requiredHits = numberOfShips * 3;
    bool playing = true;
    int lastScore = 0;
    bsLogo();
    makeEmptyBoard();
    makeBoard3(numberOfShips);
    do {
        printf("\033c");
        printBoard();
        writeLetters();
        shoot();
        if (numberOfShots == 0||numberOfHits==requiredHits) {
            playing = false;
        }
    } while (playing);
    printf("\033c");
    printPlayerBoard();
    writeLetters();
    if (numberOfShots == 0) {
        std::cout << "\n Captain, We're out of ammunition.";
        if (numberOfHits==requiredHits) {
            std::cout << "\n Yet, we managed to hit every single hostile ship!";
        }
        else {
            std::cout << "\n We are still detecting hostile ships:" << std::endl;
            printBoard();
            writeLetters();
        }
    }
    else if (numberOfHits==requiredHits) {
        std::cout << "\n We aren't detecting any more hostile ships, captain! Good shooting!";
    }

    std::cout << "\n\n Press any key to return to the main menu";
    _getch();
}

void playVsAI() {
    int numberOfShips = 3;
    int requiredHits = numberOfShips * 3;
    bool playing = true;
    int lastScore = 0;
    int playerShips = numberOfShips;
    int playerHP = playerShips * 3;
    bsLogo();
    makeEmptyBoard();
    makeBoard3(numberOfShips);
    AImakeBoard3(numberOfShips);
    do {
        printf("\033c");
        AIprintBoard();
        writeLetters();
        printBoard();
        writeLetters();
        shootAtAI();
        if (numberOfShots == 0 || numberOfHits == requiredHits) {
            playing = false;
            break;
        }
        printf("\033c");
        AIprintBoard();
        writeLetters();
        printBoard();
        writeLetters();
        AIshoot();
        if (playerHP == 0) {
            playing = false;
        }
    } while (playing);
    printf("\033c");
    AIprintBoard();
    writeLetters();
    printBoard();
    writeLetters();
    if (numberOfShots == 0) {
        std::cout << "\n Captain, We're out of ammunition.";
        if (numberOfHits == requiredHits) {
            std::cout << "\n Yet, we managed to hit every single hostile ship!";
        }
        else {
            std::cout << "\n We are still detecting hostile ships:" << std::endl;
            AIprintBoard();
            writeLetters();
        }
    }
    else if (numberOfHits == requiredHits) {
        std::cout << "\n We aren't detecting any more hostile ships, captain! Good shooting!";
    }
    else if (playerHP == 0) {
        std::cout << "\n Captain, our last ship has been sunk.";
    }
    std::cout << "\n\n Press any key to return to the main menu";
    _getch();
}