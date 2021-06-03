#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

using namespace std;

class Player
{
private:
    string *name;//holds player name
    int *score;//holds player score
    int *ansRight;//holds number of questions answered right

public:
    Player(string n);
    virtual ~Player();

    void adjustScore(int i);//adjust the score by the value supplied by the caller
    void incAnsRight();//function to increment right answers by 1

    string getName();//function to return player name
    int getScore();//function to return player score
    int getAnsRight();//return the number of questions a player answered correctly
};

#endif // PLAYER_H
