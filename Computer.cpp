#include "Computer.h"
#include <iostream>
#include <string>
#include <cstdlib> //used for rand() method to generate coords

using namespace std;

Computer::Computer(int numShips)
{
    m_board = new Board(numShips);
    m_numShips = numShips;
    m_guessedCoords = new string[81]; // maximum number of coordinates that can be guessed is 9x9=81
    m_hitCoords = new string[15]; // maximum number of coordinates that can be hit is 15, when each player has 5 ships
}
Computer::~Computer()
{
    delete m_board;
    delete m_guessedCoords;
    delete m_hitCoords;
}
int Computer::getNumShips()
{
    return(m_numShips);
}
Board* Computer::getBoard()
{
    return(m_board);
}
string* Computer::getGuessedCoords()
{
    return(m_guessedCoords);
}
int Computer::getGuessedCoords_length()
{
    return(m_guessedCoords_length);
}
string* Computer::getHitCoords()
{
    return(m_hitCoords);
}
int Computer::getHitCoords_length()
{
    return(m_hitCoords_length);
}
void Computer::placeShips()
{
    int xCoord = rand() % 9 + 1;
    int yCoord = rand() % 9 + 1;
    int numShips = this->getNumShips();
    while(numShips >= 0)
    {
        // try to place ships at given x,y coordinates
        if(/*shipPlacementSuccessful*/)
        {
            numShips--;
        }
        else
        {
            // do nothing, continue loop
        }
        
    }

}
void Computer::guessCoords_Easy(Board* playerBoard)
{
    bool doLoop = true;
    while(doLoop == true)
    {
        int x = rand() % 9 + 1;
        string xCoord = to_string(x);
        int y = rand() % 9 + 1;
        string yCoord = to_string(y);
        string Coords = xCoord + yCoord;
        bool alreadyGuessed = false;
        for(int i=0; i < getGuessedCoords_length(); i++)
        {
            if(Coords == m_guessedCoords[i])
            {
                alreadyGuessed = true;
                break;
            }
        }
        if(alreadyGuessed == false)
        {
            // shoot at the randomdly generated coordinates
            doLoop = false;
        }
    }
}
void Computer::guessCoords_Medium(Board* playerBoard)
{

}
void Computer::guessCoords_Hard(Board* playerBoard)
{
    
}