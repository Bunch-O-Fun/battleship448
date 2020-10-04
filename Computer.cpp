#include "Computer.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <cstdlib> //used for rand() method to generate coords

using namespace std;

Computer::Computer(int numShips)
{
    srand(time(NULL));
    m_board = new Board(numShips);
    m_numShips = numShips;
    m_shipsAlive = numShips;
    m_guessedCoords = new string[81]; // maximum number of coordinates that can be guessed is 9x9=81'
    for (int i = 0; i < 81; i++){
      m_guessedCoords[i] = "";
    }
    //m_hitCoords = new string[15]; // maximum number of coordinates that can be hit is 15, when each player has 5 ships
}
Computer::~Computer()
{
    delete m_board;
    delete [] m_guessedCoords;
    for (int i = 0; i < 5; i++){
        delete [] m_hitCoords[i];
    }
    delete [] m_hitCoords;
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
string** Computer::getHitCoords()
{
    return(m_hitCoords);
}
int Computer::getHitCoords_length()
{
    return(m_hitCoords_length);
}
string Computer::guessCoords_Easy()
{
    string coords;
    while(true)
    {
        int x = rand() % 9 + 1;
        int y = rand() % 9 + 1;
        coords = convertCoords(x,y);
        bool alreadyGuessed = false;
        if(m_guessedCoords_length != 0)
        {
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
                m_guessedCoords[m_guessedCoords_length+1] = coords;
                m_guessedCoords_length++;
                break;
            }
        }
        else
        {
            m_guessedCoords[m_guessedCoords_length+1] = coords;
            m_guessedCoords_length++;
            break;
        }
    }
    return(coords);
}
string Computer::guessCoords_Medium()
{
  int checkAlive = 0;
  for (int i = 0; i < m_numShips; i++){
    int health = i + 1;
    for (int j = 0; j < i + 1; j++){
      for (int k = 0; k < 81; k++){
        if(m_hitCoords[i][j] == m_guessedCoords[k]){
          health--;
          break;
        }
      }
    }
    if(health != 0){
      checkAlive++;
    }
  }
  if(checkAlive < m_shipsAlive){
    m_notSunk = false;
    m_shipsAlive--;
  }
  if(!m_notSunk){
    originX = rand() % 9 + 1;
    originY = rand() % 9 + 1;
    string guess = convertCoords(originX,originY);
    for(int i = 0; i < 81; i++){
      if(m_guessedCoords[i] == guess){
        originX = rand() % 9 + 1;
        originY = rand() % 9 + 1;
        guess = convertCoords(originX,originY);
        i = 0;
      }
      if(m_guessedCoords[i] == ""){
        m_guessedCoords[i] = guess;
        break;
      }
    }
    for (int i = 0; i < m_numShips; i++){
      for (int j = 0; j < i + 1; j++){
        if(m_hitCoords[i][j] == guess){
          m_notSunk = true;
          attackX = originX;
          attackY = originY;
          m_direction = 'U';
          return(guess);
        }
      }
    }
    return(guess);
  } else {
    string coords = "";

    if (m_direction == 'U'){
      if(getNextAttack()){
        for(int i = 0; i < 81; i++){
          if(m_guessedCoords[i] == ""){
            coords = convertCoords(attackX,attackY);
            m_guessedCoords[i] = coords;
            return(coords);
          }
        }
      } else {
        m_direction = 'D';
        attackX = originX;
        attackY = originY;
        return(guessCoords_Medium());
      }
    } else if (m_direction == 'D'){
      if(getNextAttack()){
        for(int i = 0; i < 81; i++){
          if(m_guessedCoords[i] == ""){
            coords = convertCoords(attackX,attackY);
            m_guessedCoords[i] = coords;
            return(coords);
          }
        }
      } else {
        m_direction = 'R';
        attackX = originX;
        attackY = originY;
        return(guessCoords_Medium());
      }
    } else if (m_direction == 'R'){
      if(getNextAttack()){
        for(int i = 0; i < 81; i++){
          if(m_guessedCoords[i] == ""){
            coords = convertCoords(attackX,attackY);
            m_guessedCoords[i] = coords;
            return(coords);
          }
        }
      } else {
        m_direction = 'L';
        attackX = originX;
        attackY = originY;
        return(guessCoords_Medium());
      }
    } else if (m_direction == 'L'){
        if(getNextAttack()){
          for(int i = 0; i < 81; i++){
            if(m_guessedCoords[i] == ""){
              coords = convertCoords(attackX,attackY);
              m_guessedCoords[i] = coords;
              return(coords);
            }
          }
        }


    }
      /*bool hitLocation = false;
      coords = convertCoords(attackX, attackY - 1);
      for (int i = 0; i < 81; i++){
        if(coords == m_guessedCoords[i]){
          hitLocation = true;
          if(searchHits(coords)){
asdfasdf
          }

        }
      }*/
  }
  return("AAAAAHHHHHHH"); //should never happen
}

bool Computer::getNextAttack(){
  bool nextAttack = true;
    string coords = convertCoords(attackX, attackY);
    if(m_direction == 'U'){
      while(attackY > 0){
        nextAttack = true;
        string coords = convertCoords(attackX, attackY);
        for (int i = 0; i < 81; i++){
          if(coords == m_guessedCoords[i]){
            if(!searchHits(coords)){
              return false;
            }
            nextAttack = false;
            attackY--;
            break;
          }
        }
        if(nextAttack){
          return nextAttack;
        }
        if(attackY == 0){
          return false;
        }
      }
    } else if (m_direction == 'D'){
      while(attackY < 10){
        nextAttack = true;
        string coords = convertCoords(attackX, attackY);
        for (int i = 0; i < 81; i++){
          if(coords == m_guessedCoords[i]){
            if(!searchHits(coords)){
              return false;
            }
            nextAttack = false;
            attackY++;
            break;
          }
        }
        if(nextAttack){
          return nextAttack;
        }
        if(attackY == 10){
          return false;
        }
      }
    } else if (m_direction == 'R'){
      while(attackX < 10){
        nextAttack = true;
        string coords = convertCoords(attackX, attackY);
        for (int i = 0; i < 81; i++){
          if(coords == m_guessedCoords[i]){
            if(!searchHits(coords)){
              return false;
            }
            nextAttack = false;
            attackX++;
            break;
          }
        }
        if(nextAttack){
          return nextAttack;
        }
        if(attackX == 10){
          return false;
        }
      }
    }else if (m_direction == 'L'){
      while(attackX > 0){
        nextAttack = true;
        string coords = convertCoords(attackX, attackY);
        for (int i = 0; i < 81; i++){
          if(coords == m_guessedCoords[i]){
            if(!searchHits(coords)){
              return false;
            }
            nextAttack = false;
            attackX--;
            break;
          }
        }
        if(nextAttack){
          return nextAttack;
        }
        if(attackX == 0){
          return false;
        }
      }
    }
    cout << "something went wrong\n";
    return(false);

}

bool Computer::searchHits(string guess){
  for (int i = 0; i < m_numShips; i++){
    for (int j = 0; j < i + 1; j++){
      if(m_hitCoords[i][j] == guess){
        return true;
      }
    }
  }
  return false;
}


string Computer::guessCoords_Hard()
{
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < i + 1; j++){
            if(m_hitCoords[i][j] != ""){
                string attack = m_hitCoords[i][j];
                m_hitCoords[i][j] = "";
                cout << attack << "\n";
                return attack;
            }
        }
    }
    return("AAAAHHHHHHH"); //should never return
}

void Computer::sethitCoords(string** hit){
    m_hitCoords = hit;
}
