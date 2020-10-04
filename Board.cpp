/* -----------------------------------------------------------------------------

@author Abhigyan Saxena, Xiaoyi Lu, Evelyn Thomas, @file Board.cpp, @date 09/12/20, @brief Board functions implemented

 ---------------------------------------------------------------------------- */
#include "Board.h"
#include <sstream>
#include <limits>
#include <cstdlib> //used for the rand() to randomly generate coordinates for the computer to attack
using namespace std;

Board::Board(int shipnum)
{
	numberOfShips = shipnum;	//the number of ships per player.
	blueTilde = "\033[1;36m~\033[0m";	//blue water color
	redHit = "\033[1;31mX\033[0m";	//red ship hit color
	whiteMiss = "\033[1;37mO\033[0m";		//white missed shot color
		//green ship color

	for (int i=0; i<9; i++)	//initializes myBoard and shotBoard to a grid of blue water
	{
		for(int j=0; j<9; j++)
		{
			myBoard[i][j] = blueTilde;
			shotBoard[i][j] = blueTilde;
		}
	}
}
string** Board::getFleet(){
	string** fleetList = new string*[5];
	for (int i=0; i < 5; i++){
		fleetList[i] = new string[i + 1];
		for(int j = 0; j < i + 1; j++){
			fleetList[i][j] = "";
		}
	}
	for(int i = 0; i < 5; i++){
		int fill = 0;
		for(int y = 0; y < 9; y++){
			for(int x = 0; x < 9; x++){
				if (myBoard[x][y] == ship[i]){
					fleetList[i][fill] = convertCoords(y + 1,x + 1);
					fill++;
				}
			}
		}
	}
	return fleetList;
} 
Board::~Board()	//destructor to delete m_ship
{
	delete[] m_ship;
}
void Board::printMyBoard()	//prints the player's board
{
	std::cout << "\t\t\tYour board\n";
	std::cout << "\t";
	for(int i=0;i<9;i++)
	{
		std::cout << m_rowNames[i] << "\t";	//prints the columns
	}
	std::cout << "\n";
	for(int i=0;i<9;i++)
	{
		std::cout << i+1;	//print the rows
		for(int j=0;j<9;j++)
		{
			std::cout << "\t" << myBoard[i][j];	//print the board symbols
		}
		if(i<9) //reduce space
		{
			std::cout << "\n\n\n";
		}
		else
		{
			std::cout << "\n\n";
		}
	}
}
void Board::printMyScoreBoard(int num)
{
	std::cout<<"\n";
	std::cout<<"=========SCOREBOARD==========\n";
	std::cout<<"Ship Status: \n";
		if (m_ship[0].isSunk() == 1 && num >= 1) // checks if size 1 ship is sunk or not
			{
				std::cout<<"Size 1: Sunk\n";
			}
		else if (num >=1)
		{
			std::cout<<"Size 1: Alive\n";
		}
		if (m_ship[1].isSunk() == 1 && num >= 2) // checks if size 2 ship is sunk or not
		{
			std::cout<<"Size 2: Sunk\n";
		}
		else if (num >=2)
		{
			std::cout<<"Size 2: Alive\n";
		}
		if (m_ship[2].isSunk() == 1 && num >= 3) // checks if size 3 ship is sunk or not
		{
			std::cout<<"Size 3: Sunk\n";
		}
		else if (num >=3)
		{
			std::cout<<"Size 3: Alive\n";
		}
		if (m_ship[3].isSunk() == 1 && num >= 4) // checks if size 4 ship is sunk or not
		{
			std::cout<<"Size 4: Sunk\n";
		}
		else if (num >=4)
		{
			std::cout<<"Size 4: Alive\n";
		}
		if (m_ship[4].isSunk() == 1 && num >= 5) // checks if size 5 ship is sunk or not
		{
			std::cout<<"Size 5: Sunk\n";
		}
		else if (num>=5)
		{
			std::cout<<"Size 5: Alive\n";
		}
	std::cout<<"\n";
}
bool Board::updateMyBoard(std::string userGuess)	//updates the current player board
{
	guessConversion(userGuess);	//updates m_rowIndex and m_columnIndex based on userGuess
	std::string location = myBoard[m_rowIndex][m_columnIndex];	//sets the location to the current element in the index that the player got shot at
	if(location == blueTilde)	//if location is water, then it is a miss
	{
		myBoard[m_rowIndex][m_columnIndex] = whiteMiss;
	}
	else if(location == redHit || location == whiteMiss)	//can't shoot at same location twice
	{
		throw(std::runtime_error("You already shot here! Try again!"));
	} else	{//if location is a green triangle, then set to a red traingle
		myBoard[m_rowIndex][m_columnIndex] = redHit;
		for(int i = 0; i < numberOfShips; i++)	//searches through each ship, at the length of each ship, until it finds the correct index holding the userGuess location
		{
			for(int j = 0; j < m_ship[i].getLength(); j++)
			{
				if(m_ship[i].getCoordinate(j) == userGuess)
				{
					m_ship[i].addDamage();	//damage++
					if(m_ship[i].isSunk())	//if damage counter equal to length, it has sunk
					{
						std::cout << "BATTLESHIP SUNK!\n";	//prints that the ship has been sunk
					}
					break;
				}
			}
		}
		return true;	//true, ship hit
	}
	return false;	//if there were no hits, then this runs and we return false because it was a miss
}
void Board::printShotBoard()	//prints rival board
{
	std::cout << "\n\t\t\tYour Rival's board\n";
	std::cout << '\t';
	for(int i=0;i<9;i++)
	{
		std::cout << m_rowNames[i] << "\t";	//prints the column names
	}
	std::cout << "\n";
	for(int i=0;i<9;i++)
	{
		std::cout << i+1;	//prints the row names
		for(int j=0;j<9;j++)
		{
			std::cout << "\t" << shotBoard[i][j];	//print the board symbols
		}
		if(i != 8)
		{
			std::cout << "\n\n\n"; //space b/w rows
		}
		else
		{
			std::cout << "\n\n"; //space b/w rows
		}
	}
}
void Board::updateShotBoard(std::string userGuess, bool wasHit)
{
	guessConversion(userGuess);
	if(wasHit)	//redHit for hit
	{
		shotBoard[m_rowIndex][m_columnIndex] = redHit;
	}
	else	//whiteMiss for miss
	{
		shotBoard[m_rowIndex][m_columnIndex] = whiteMiss;
	}
}
void Board::guessConversion(std::string userGuess)
{
	if(userGuess.length() != 2)	//if it isn't a coordinate like "A2, B7" etc. we return so user can try agane
	{
		return;
	}
	else
	{
	for(unsigned int i=0;i<m_rowNames.length();i++)
	{
		if(userGuess.at(0) == m_rowNames.at(i) ||userGuess.at(0) == (tolower(m_rowNames.at(i))))
		{
			m_columnIndex = i;
			break;
		}
		else
		{
			m_columnIndex = 10;
		}
	}
}
	int temp = userGuess.at(1) - '0'; //convert ASCII to decimal
	m_rowIndex = temp - 1; //sets the column user wants, -1 for computer scientist index :)
}
bool Board::withinBoundary(std::string userGuess) //true for userGuess within bounds of the board
{
	if(userGuess.length() != 2)
		{
			return false;
		}
		else
		{
			guessConversion(userGuess);
			if((0 <= m_rowIndex && m_rowIndex <= 8) && (0 <= m_columnIndex && m_columnIndex <= 8))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
}
bool Board::noHorizontalCollision(std::string userGuess, int shipLength)
{
	guessConversion(userGuess);
	for(int i = 0; i < shipLength; i++)
	{
		if((0 <= m_rowIndex && m_rowIndex <= 8) && (0 <= m_columnIndex + i && m_columnIndex + i <= 8))	//checks indices within boundary
			{
			if(myBoard[m_rowIndex][m_columnIndex + i] != blueTilde)	//returns false if right indices are not water
				{
				return false;
				}
			}
		else
		{
			return false;	//false if out of bounds
		}
	}
 	return true;	//passed all checks, no collosion
}
bool Board::noVerticalCollision(std::string userGuess, int shipLength)
{
	guessConversion(userGuess);
	for(int i = 0; i < shipLength; i++)
 	{
		if((0 <= m_rowIndex + i && m_rowIndex + i <= 8) && (0 <= m_columnIndex && m_columnIndex <= 8))
		{
			if(myBoard[m_rowIndex + i][m_columnIndex] != blueTilde)	//false if not on water
			{
				return false;
			}
		}
		else
		{
			return false;	//false if out of bounds
		}
 	}
 	return true;	//if passes all checks, no cblank space to hide the board from the other playerollision
}
string Board::convertCoords(int x, int y) //converts coordinates from two intger values to a string of the form "A1" or "C7"
{
	string xCoord = "";
    string yCoord = to_string(y);
    string convertedCoords = "";
    if(x < 0 || x > 9)
    {
        //coordinates passed in will only be in the range 0 to 9 thanks to rand() function
    }
    else if(x == 1)
    {
        xCoord = 'A';
    }
    else if(x == 2)
    {
        xCoord = 'B';
    }
    else if(x == 3)
    {
        xCoord = 'C';
    }
    else if(x == 4)
    {
        xCoord = 'D';
    }
    else if(x == 5)
    {
        xCoord = 'E';
    }
    else if(x == 6)
    {
        xCoord = 'F';
    }
    else if(x == 7)
    {
        xCoord = 'G';
    }
    else if(x == 8)
    {
        xCoord = 'H';
    }
    else if(x == 9)
    {
        xCoord = 'I';
    }
    convertedCoords += xCoord;
    convertedCoords = convertedCoords + yCoord;
    return(convertedCoords);
}
void Board::setupBoard(bool isPlayer)
{
	std::string userGuess;
	std::string userDirection;
	bool validLocation = false;
	std::string temp;
	bool HorV = false;
	m_ship =  new Ship[numberOfShips];
	for(int i = 0; i < numberOfShips; i++)
	{
		m_ship[i].createShip(i+1);
		if(m_ship[i].getLength() == 1)
		{
			userGuess = " ";
				do {
					if (isPlayer)
					{
						printMyBoard();
						std::cout<<"Where would you like to place this ship of size 1? Enter your coordinate: (LETTER,NUMBER)\n";
						std::cin>>userGuess;
					}
					else
					{
						userGuess = convertCoords(rand()%9+1, rand()%9+1);
					}
					std::transform(userGuess.begin(), userGuess.end(),userGuess.begin(), ::toupper);
					if(!withinBoundary(userGuess))
					{
						std::cout << "Invalid Location, Try again!\n";
					}
				} while(!withinBoundary(userGuess));
					myBoard[m_rowIndex][m_columnIndex] = ship[0];
					m_ship[i].setCoordinate(userGuess, 0);
					if(isPlayer)
					{
						printMyBoard();
					}
		}
		else
		{
			if(isPlayer)
			{
				std::cout<<"Your next ship is size " <<i+1<< ", which way do you want this ship to face? HORIZONTAL(H/h) OR VERTICAL(V/v)\n";
				std::cin>>userDirection;
			}
			else
			{
				if(rand()%2)
				{
					userDirection = "H";
				}
				else
				{
					userDirection = "V";
				}
			}
			do
			{
				HorV = false;
				if(userDirection == "H" || userDirection == "h")
				{
					validLocation = false;
					if(isPlayer)
					{
						std::cout<<"Type in the left most coordinate of this ship on the board to place it? (LETTER,NUMBER)\n";
						std::cin>>userGuess;
					}
					else
					{
						userGuess = convertCoords(rand()%9+1, rand()%9+1);
					}
					std::transform(userGuess.begin(), userGuess.end(),userGuess.begin(), ::toupper);
					while(validLocation == false)
					{
						if(noHorizontalCollision(userGuess,i+1))	//collion check
						{
							guessConversion(userGuess);
							temp = userGuess;
							for(int j = 0; j < m_ship[i].getLength(); j++ )
							{
								myBoard[m_rowIndex][m_columnIndex+j] = ship[i];
								m_ship[i].setCoordinate(temp, j);
								temp[0] = temp.at(0) + 1;
							}
							if(isPlayer)
							{
								printMyBoard();
							}
							validLocation = true;
							HorV = true;
						}
						else
						{
							if(isPlayer)
							{
								printMyBoard();
								std::cout << "Invalid Location, Try again!\n";
								std::cout<<"Type in the left most coordinate of this ship to place it on the board? (LETTER,NUMBER)\n";
								std::cin>>userGuess;
							}
							else
							{
								userGuess = convertCoords(rand()%9+1, rand()%9+1);
							}
							std::transform(userGuess.begin(), userGuess.end(),userGuess.begin(), ::toupper);
						}
					}
				}
				else if(userDirection == "V" || userDirection == "v")
				{
					validLocation = false; //reinitializes to false since if they do H twice in a row, it could have been set to true from before
					if(isPlayer)
					{
						std::cout<<"Type in the top most coordinate of this ship to place it on the board? (LETTER,NUMBER)\n";
						std::cin>>userGuess;
					}
					else
					{
						userGuess = convertCoords(rand()%9+1, rand()%9+1);
					}
					std::transform(userGuess.begin(), userGuess.end(),userGuess.begin(), ::toupper);
					while(validLocation == false)
					{
						if(noVerticalCollision(userGuess,i+1))
						{
							guessConversion(userGuess);
							temp = userGuess;
							for(int j = 0; j < m_ship[i].getLength(); j++ )
							{
								myBoard[m_rowIndex+j][m_columnIndex] = ship[i];
								m_ship[i].setCoordinate(temp, j);
								temp[1] = temp.at(1) + 1;
							}
							if(isPlayer)
							{
								printMyBoard();
							}
							validLocation = true;
							HorV = true;
						}
						else
						{
							if(isPlayer)
							{
								printMyBoard();
								std::cout << "Invalid Location, Try again!\n";
								std::cout<<"Type in the top most coordinate of this ship to place it on the board? (LETTER,NUMBER)\n";
								std::cin>>userGuess;
							}
							else
							{
								userGuess = convertCoords(rand()%9+1, rand()%9+1);
							}
							std::transform(userGuess.begin(), userGuess.end(),userGuess.begin(), ::toupper);	//converts guess to uppercase
						}
					}
				}
				else
				{
					std::cout << "Invalid Direction. Try again!\n";
					printMyBoard();
					std::cout<<"Your next ship is size " <<i+1<< ", which way do you want this ship to face? HORIZONTAL(H/h) OR VERTICAL(V/v)\n";
					std::cin>>userDirection;
				}
			}while(!HorV);
		}
	}
	if(isPlayer)
	{
		std::cout << "Press Enter to go to the next Player's turn: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		printIntermission();
	}
}
void Board::setNumberofShips(int shipnum)
{
	numberOfShips = shipnum;
}
int Board::getNumberofShips() const
{
	return numberOfShips;
}
Ship* Board::getShip() const
{
	return m_ship;
}
void Board::printIntermission()
{
	for(int i=0;i<40;i++)
	{
		std::cout << "\n\n\n\n\n\n";	//print blank space
	}
	std::cout << "Press Enter when ready! ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');	//ignore all input except enter .. mainly for friendly smack talking
}