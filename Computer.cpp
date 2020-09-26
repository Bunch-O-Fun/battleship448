#include "Computer.h"
#include "Player.h"
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
string Computer::convertCoords(int x, int y)
{
    string xCoord = "";
    string yCoord = to_string(y);
    string convertedCoords = "";
    if(x < 0 || x > 9)
    {
        // some sort of error message
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
string Computer::guessCoords_Easy()
{
    bool doLoop = true;
    while(doLoop == true)
    {
        int x = rand() % 9 + 1;
        int y = rand() % 9 + 1;
        string coords = convertCoords(x,y);
        bool alreadyGuessed = false;
        for(int i=0; i < m_guessedCoords_length; i++)
        {
            if(coords == m_guessedCoords[i])
            {
                alreadyGuessed = true;
                break;
            }
        }
        if(alreadyGuessed == false)
        {
            m_guessedCoords[getGuessedCoords_length()+1] = coords;
            m_guessedCoords_length++;
            doLoop = false;
            return(coords);
        }
    }
}
string Computer::guessCoords_Medium()
{

}
string Computer::guessCoords_Hard()
{

}