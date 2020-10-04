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
        string** m_hitCoords = nullptr; // stores the hit coordinates in an array of strings
        int m_hitCoords_length = 0; // keeps track of the number of hit coordinates that have been put in the array
        //int* m_numPlayerShips;
        int m_expectedNumShips;
        char m_direction = 'U';
        bool m_notSunk = false;
        int originX;
        int originY;
        int attackX;
        int attackY;
        int m_shipsAlive;
    public:
        /**
	      * @pre: Computer class constructor
	      * @post: Creates a new board for the computer and an array of guessed coordinates
	      * @param: numShips
	      */
        Computer(int numShips);

        /**
	      * @pre: Computer class destructor
	      * @post:
	      */
        ~Computer();
        /**
	      * @param: valid coordinates
          * @return: a string of coordinates
	      */
        string convertCoords(int x, int y);
        /**
          * @pre: ship must be placed
          * @return: number of ships on the board
	      */
        int getNumShips();
        /**
          * @pre: board must exist
          * @return: returns the computer board
	      */
        Board* getBoard();
        /**
          * @pre: coordinates must be guessed
          * @return: returns an array of guessed coordinates
	      */
        string* getGuessedCoords();
        /**
          * @pre: coordinates must be guessed
          * @return: returns the amount of coordinates in the guessedCoords array
	      */
        int getGuessedCoords_length();
        /**
          * @pre: coordinates must be guessed
          * @return: returns a 2D array of hit coordinates
	      */
        string** getHitCoords();
        /**
          * @pre: array must exist
          * @return: returns the amount of coordinates in the hitCoords array
	      */
        int getHitCoords_length();
        /**
          * @post: guesses random coordinates on the board to be hit
          * @return: returns a string of a coordinate to be hit
	      */
        string guessCoords_Easy();
        /**
          * @post: guesses random coordinates on the board to be hit
          *        After it hits a ship, it checks around nearby coordinates until the ship is sunk
          * @return: returns a string of a coordinate to be hit
	      */
        string guessCoords_Medium();
        /**
          * @post: shoots at a ship coordinate, not really a guess
          * @return: returns a string of a coordinate to be hit
	      */
        string guessCoords_Hard();
        /**
          * @post: declares a coordinate to be hit
	      */
        void sethitCoords(string** hit);
        /**
          * @pre: have array of player's coordinates
          * @param: string of the coord you want to search
          * @return:true if that coord is a player coordinate
	      */
        bool searchHits(string guess);
        /**
          * @return:true if can attack in a direction
          * @post: attackX and Y are set to next available attack position
	      */
        bool getNextAttack();
};
#endif
