#ifndef COMPUTER_H
#define COMPUTER_H

#include "Board.h"
#include <string>

using namespace std;

class Computer
{
    private:
        int m_numShips; // number of ships selected for the game
        Board* m_board = nullptr; // Computer's board
        string* m_guessedCoords = nullptr; // stores the guessed coordinates in an array of strings
        int m_guessedCoords_length = 0; // keeps track of the number of guessed coordinates that have been put in the array
        string* m_hitCoords = nullptr; // stores the hit coordinates in an array of strings
        int m_hitCoords_length = 0; // keeps track of the number of hit coordinates that have been put in the array
    public:
        Computer(int numShips);
        ~Computer();
        string convertCoords(int x, int y);
        int getNumShips();
        Board* getBoard();
        string* getGuessedCoords();
        int getGuessedCoords_length();
        string* getHitCoords();
        int getHitCoords_length();
        void placeShips();
        string guessCoords_Easy();
        string guessCoords_Medium();
        string guessCoords_Hard();
};
#endif