#include "Player.h"

/**< construnctor */
Player::Player(string n)
{
    /**< allocating memory to the variables */
    name = new string ;//holds player name
    score = new int;//holds player score
    ansRight = new int;//holds number of questions answered right

    /**< initialising the pointers */
    *name = n;
    *score = 0;
    *ansRight = 0;
}

/**<destructor*/
Player::~Player()
{
    delete name;
    delete score;
    delete ansRight;
}

/**< adjust the score by the value supplied by the caller */
void Player::adjustScore(int i)
{
    *score += i;
}

/**< function to increment right answers by 1 */
void Player::incAnsRight()
{
    *ansRight += 1;
}

/**< function to return player name */
string Player::getName()
{
    return *name;
}

/**< function to return player score */
int Player::getScore()
{
    return *score;
}

/**< function to return the number of questions a
player answered correctly */
int Player::getAnsRight()
{
    return *ansRight;
}


