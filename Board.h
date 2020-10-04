/* -----------------------------------------------------------------------------

@author Abhigyan Saxena, Xiaoyi Lu, Evelyn Thomas, @file Board.h, @date 09/12/20, @brief declares Board methods

 ---------------------------------------------------------------------------- */
#ifndef BOARD_H
#define BOARD_H
#include "Ship.h"
#include "algorithm"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Board
{
        private:
        	string shotBoard[9][9];
		string myBoard[9][9];
		string m_rowNames = "ABCDEFGHI";
		string m_columnNames = "123456789";
		int m_rowIndex;
		int m_columnIndex;
		/**
		* 	@pre none
		*	@param takes a location string from user
		*	@post converts userGuess to two array indices, updating rowIndex and columnIndex
		*/
		void guessConversion(std::string userGuess);
		string blueTilde;
		string redHit;
		string whiteMiss;
		string ship[5] = {"\033[1;32mD\033[0m", "\033[1;32mG\033[0m", "\033[1;32mS\033[0m", "\033[1;32mB\033[0m", "\033[1;32mC\033[0m"};
		int numberOfShips;
		Ship* m_ship = nullptr;

        public:
                string** getFleet();
        	Board();
        	~Board();
		/**
       		  * @pre None
       		  * @post constructor
       		  * @param shipNum
       		  * @throw None
       		  */
		Board(int shipNum);
		/**
       		  * @pre None
       		  * @post prints rival's board
       		  * @param None
       		  * @throw None
       		  */
		void printShotBoard();
		/**
                  * @pre None
                  * @post prints player's board
                  * @param None
                  * @throw None
                  */
		void printMyBoard();
		/**
                * @pre None
                * @post prints blank space to hide the board from the other player
                * @param None
                * @throw None
                */
                void printMyScoreBoard(int num);
		/**
                * @pre None
                * @post prints and updates the scoreboard
                * @param Takes in amount of ships
                * @throw None
                */
		void printIntermission();
		/**
                  * @pre None
                  * @post sets the number of ships
                  * @param an integer called shipnum
                  * @throw None
                  */
		void setNumberofShips(int shipnum);
		/**
                  * @pre None
                  * @post gets the number of ships
                  * @param None
                  * @throw None
                  */
		int getNumberofShips() const;
		/**
                  * @pre None
                  * @post sets the board up for the players
                  * @param None
                  * @throw None
                  */
		void setupBoard(bool isPlayer);
		/**
                  * @pre None
                  * @post updates the shot board based on whether a location with a ship was hit or not
                  * @param userGuess, wasHit
                  * @throw None
                  */
		void updateShotBoard(std::string userGuess, bool wasHit);
		/**
                  * @pre None
                  * @post Updates the player's board
                  * @param userGuess
                  * @throw If the user guesses a location that was shot before, a runtime error is thrown
                  */
		bool updateMyBoard(std::string userGuess);
		/**
                  * @pre None
                  * @post checks if the guess is within bounds or not. Based on the check, it returns true or false.
                  * @param userGuess
                  * @throw None
                  */
		bool withinBoundary(std::string userGuess);
		/**
                  * @pre None
                  * @post checks whether the horizontally placed ship will collide with another ship. Based on this, it returns true or false.
                  * @param userGuess, shipLength
                  * @throw None
                  */
		bool noHorizontalCollision(std::string userGuess, int shipLength);
		/**
                  * @pre None
                  * @post checks whether the vertically placed ship will collide with another ship. Based on this, it returns true or false
                  * @param userGuess, shipLength
                  * @throw None
                  */
		bool noVerticalCollision(std::string userGuess, int shipLength);
                /**
                  * @pre None
                  * @post gets ship object
                  * @param None
                  * @throw None
                  */
		Ship* getShip() const;
                /**
                  * @pre None
                  * @post converts a set of integer coordinates to a string
                  * @param x, y coordinates
                  * @throw None
                  */
                string convertCoords(int x, int y);
};
#endif
