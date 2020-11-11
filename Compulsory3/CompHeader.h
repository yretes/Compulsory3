#pragma once
#include <iostream>
#include "CompHeader.h"
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <ctime>



void passcodeInput();
bool sameCode(char input[], char fasit[]);
void passcodeSet();
void menu();
void bsLogo();
char capitalize(char letter);
int letterToNumber(char letter);
char numberToLetter(int number);
void makeEmptyBoard();
int randomRow();
int randomColumn();
void writeLetters();
void makeBoard(int numberOfShips);
void makeBoard3(int numberOfShips);
void printBoard();
void printPlayerBoard();
void shoot();
void play();
bool isVerticalRNG();
void AImakeBoard3(int numberOfShips);
void playVsAI();
void AIprintBoard();
void shootAtAI();