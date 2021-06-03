#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Complex.h"
#include "Player.h"
#include <windows.h>
#include <mmsystem.h>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

/**< this struct holds the top 10 names & corresponding scores of players */
struct Game
{
    int topScores[100];//holds the top 10 scores
    string topNames[100];//holds the top 10 players names
    /**< both arrays have a capacity of 100 to compensate for new incoming players */
};
/**< ---------------------------------------------------------------------------------------------- */

void printTextfile(string strFile);/**< prints a text file */
int random();/**< generates a random integer */
char genType();/**< generates a type of operator(+,-,x) for the complex question */
int calcScore(Player *player, int time);/**< calculates the player score */

/**< method to play background music */
void play_music()
{
    while (true)
    {
        srand(time(0));
        int pick = rand()%3;//generates a random number to pick a random song

        if (pick == 0)
        {
            PlaySound("Smooth Jazz - Part 1.wav", NULL, SND_FILENAME|SND_SYNC);
        }
        else if (pick == 1)
        {
            PlaySound("Smooth Jazz - Part 2.wav", NULL, SND_FILENAME|SND_SYNC);
        }
        else if (pick == 2)
        {
            PlaySound("Smooth Jazz - Part 3.wav", NULL, SND_FILENAME|SND_SYNC);
        }
    }
}
/**< ---------------------------------------------------------------------------------------------- */

/**< inserts a variable into an array which can be an integer(topScores) or a string(topNames)*/
template <typename type>
void Insert(type arr[], int n, int Pos, type Data)
{
    for (int C=n; C>=Pos; C--)
    {
        arr[C]=arr[C-1];
    }
    arr[Pos-1]=Data;
}
/**< ---------------------------------------------------------------------------------------------- */

/**< prints the leader board with formatting*/
void printBoard(const Game &board)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    printTextfile("Headings//Leader Board Header.txt");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << fixed;
    cout << setw(21) << left << "" <<  setw(29) << left << "-----------------------------" << endl;
    cout << setw(21) << left << "" <<  setw(25) << left << "         LEADER BOARD" << endl;
    cout << setw(21) << left << "" <<  setw(25) << left << "-----------------------------" << endl;
    cout << setw(25) << left << "" <<  setw(20) << left << "Name:" << //4
         setw(5) << left << "Score:" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << fixed;
        string pos = to_string(i+1) + ".";
        cout << setw(21) << left << "" << setw(4) << left << pos <<  setw(20) << left << board.topNames[i] <<
             setw(5) << left << board.topScores[i] << endl;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
/**< ---------------------------------------------------------------------------------------------- */

HANDLE wHnd;// Handle to write to the console.
HANDLE rHnd;// Handle to read from the console.

/**< MAIN() */
int main()
{
    // Set up the handles for reading/writing:
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    // Change the window title:
    SetConsoleTitle("Advanced C Game - Complex Math");
    // Set up the required window size:
    SMALL_RECT windowSize = {0, 0, 78, 30};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
    // Change the console window size:
    // Create a COORD to hold the buffer size:
    COORD bufferSize = {10, 10};
    SetConsoleScreenBufferSize(wHnd, bufferSize);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//sets console text colour to bright white
    // Exit

    thread t(play_music);//plays music simultaneously in the background

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    printTextfile("Headings//Welcome Complex.txt");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    printTextfile("Headings//Welcome Math.txt");
    cout<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    /**< Gives the player an option to view the rules of the game*/
    char op = 'N';//variable to hold the response to an option from a player
    cout << "View help? (Y)/(N): ";
    cin >> op;
    if((op == 'Y') || (op == 'y'))
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout<<"---------------------------------------------------------------------------------"<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        printTextfile("Headings//Help Header.txt");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        printTextfile("Help.txt");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    /**< ---------------------------------------------------------------------------------------------- */

    char playAgain;//holds a char input that determines if the player wants to play again
    Game board;//holds an instance of the leader board

    do
    {
        /**< Game mode selection - the player selects the mode of the game*/
        cout << "Type in the mode you would like to play: (M)ulti/(S)ingle: ";
        cin >> op;
        cout << endl;
        /**< ---------------------------------------------------------------------------------------------- */

        /**<
        This section of code extracts information about the top 10 players &
        copies that data into arrays correpsponding with the players names(topNames)
        & their scores(topScores)
        */
        string sName;//holds the player's name
        string sScore;//holds the player's score
        int pos;//holds positions in a leader board
        ifstream inTopNames, inTopScores;//placeholders for textfiles
        inTopNames.open ("topNames.txt");
        inTopScores.open ("topScores.txt");
        if (inTopNames && inTopScores)
        {
            pos = 0;
            while(!inTopNames.eof()) // To get you all the lines.
            {
                getline(inTopNames,sName);// Saves the line in sName.
                getline(inTopScores,sScore);
                board.topNames[pos] = sName;
                board.topScores[pos] = stoi(sScore);
                pos += 1;
            }
            inTopNames.close();
            inTopScores.close();
        }
        else
        {
            cout << "File/s do not exist." << endl;
        }
        /**< ---------------------------------------------------------------------------------------------- */


        if((op == 'M') || (op == 'm'))
        {
            /**< Each player enters their name & are welcomed to the game */
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
            printTextfile("Headings//Multiplayer Header.txt");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            string name;//holds the players names
            cout << "                   Player 1 please enter your name: ";
            cin.ignore( numeric_limits<streamsize>::max(), '\n'); //must eliminate characters in buffer
            getline(cin, name); //Will get the line, where as cin only gets the token
            Player *player1;//creates an instance of player 1
            player1 = new Player(name);
            cout << "                       Welcome to the game " << player1->getName() << " !" << endl;
            cout << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << "                   Player 2 please enter your name: ";
            //cin.ignore( numeric_limits<streamsize>::max(), '\n'); //must eliminate characters in buffer
            getline(cin, name); //Will get the line, where as cin only gets the token
            Player *player2;//creates an instance of player 2
            player2 = new Player(name);
            cout << "                        Welcome to the game " << player2->getName() << " !" <<endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout<<endl;
            /**< ---------------------------------------------------------------------------------------------- */

            /**< Multiplayer Mode Logic */
            for (int i = 1; i < 3; i++)//looped twice for player 1 & player 2
            {
                int playerCounter = i;
                char ready = 'N';//holds player repsonse
                cout<<"---------------------------------------------------------------------------------"<<endl;
                do
                {
                    if(i == 1)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                    }
                    else{

                        cout<<endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                    }
                    cout << "                          PLAYER " << i << " START? (Y): " ;
                    cin >> ready;
                    cout <<endl;
                }
                while( (ready != 'y') && (ready != 'Y') );

                chrono::steady_clock::time_point begin = chrono::steady_clock::now();
                for (int i = 1; i < 31; i++)
                {
                    Complex c1(random(), random());
                    Complex c2(random(), random());
                    Complex c3;
                    char type = genType();
                    if (type == '+')
                    {
                        c3 = c1 + c2;

                    }
                    else if (type == '-')
                    {
                        c3 = c1 - c2;
                    }
                    else if (type == 'x')
                    {
                        c3 = c1 * c2;
                    }

                    if(playerCounter == 1)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                    }
                    else{
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                    }
                    cout << "                               Question " << i << "/30 :"<<endl;
                    cout << "                         (";
                    c1.print();
                    cout << ")" << type << "(";
                    c2.print();
                    cout << ") = ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    string answer;
                    cin >> answer;
                    bool right = c3.checkCorrect(answer);
                    if (right == true)
                    {
                        if (i == 1)
                            player1->incAnsRight();
                        else
                            player2->incAnsRight();
                    }
                    cout << endl;

                }

                if(i == 1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                }
                else
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                }
                chrono::steady_clock::time_point end = chrono::steady_clock::now();
                int time = chrono::duration_cast<chrono::seconds>(end - begin).count();
                cout << "                            Time taken: " << time << "s" << endl;
                if (i == 1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);//sets text to blue
                    cout << "                          Your score is " << calcScore(player1, time) << endl;
                    cout<<endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//sets text to white
                }
                else
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                    cout << "                          Your score is " << calcScore(player2, time) << endl;
                    cout << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout<<"---------------------------------------------------------------------------------"<<endl;
            cout<<endl;
            /**< ---------------------------------------------------------------------------------------------- */

            /**< Decides whether a player loses, wins or draws & displays the message */
            if (player1->getScore() > player2->getScore())
            {
                cout << fixed;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                cout << setw(25) << left << "" << setw(8) << left << "      WINNER:" << setw(20)<< left << player1->getName() << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                cout << setw(25) << left << "" << setw(8) << left << "      LOSER:" << setw(20)<< left << player2->getName() << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            else if (player1->getScore() < player2->getScore())
            {
                cout << fixed;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                cout << setw(25) << left << "" << setw(8) << left << "      WINNER:" << setw(20)<< left << player2->getName() << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                cout << setw(25) << left << "" << setw(8) << left << "      LOSER:" << setw(20)<< left << player1->getName() << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            else
            {
                cout << "                       " << player1->getName() << " and " << player2->getName() << " have DRAWN!" << endl;
            }
            /**< ---------------------------------------------------------------------------------------------- */

            /**<
            This section of code decides if a player qualfies for a spot in the top 10
            & if, so their information will be recorded */
            for (int j = 1; j < 3; j++)
            {
                for (int i = 0; i < 10; i++)
                {
                    if (j == 1)
                    {
                        if (player1->getScore() > board.topScores[i])
                        {
                            Insert(board.topNames, 10, (i+1), player1->getName());
                            Insert(board.topScores, 10, (i+1), player1->getScore());
                            break;
                        }
                    }
                    else
                    {
                        if (player2->getScore() > board.topScores[i])
                        {
                            Insert(board.topNames, 10, (i+1), player2->getName());
                            Insert(board.topScores, 10, (i+1), player2->getScore());
                            break;
                        }
                    }
                }
            }
            /**< ---------------------------------------------------------------------------------------------- */

            delete player1;//destroys the player object
            delete player2;//destroys the player object
        }

        else if ((op == 'S') || (op == 's'))
        {
            /**< Player enters their name & are welcomed to the game */
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
            printTextfile("Headings//Single Player Header.txt");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            string name;//holds player name
            cout << "                        Please enter your name: ";
            cin.ignore( numeric_limits<streamsize>::max(), '\n'); //must eliminate characters in buffer
            getline(cin, name); //Will get the line, where as cin only gets the token

            Player *player1;//creates player 1
            player1 = new Player(name);

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            cout << "                         Welcome to the game " << player1->getName() <<" !" << endl;
            cout<<endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout<<"---------------------------------------------------------------------------------"<<endl;
            cout<<endl;

            char ready = 'N';
            do
            {
                cout << "                             BEGIN GAME? (Y): "; //9 tabs
                cin >> ready;
                cout <<endl;
            }
            while( (ready != 'y') && (ready != 'Y') );

            chrono::steady_clock::time_point begin = chrono::steady_clock::now();
            /**< ---------------------------------------------------------------------------------------------- */

            /**< Single player Mode Logic */
            for (int i = 1; i < 31; i++)//30 loops for 30 questions
            {
                Complex c1(random(), random());
                Complex c2(random(), random());
                Complex c3;
                char type = genType();
                if (type == '+')
                {
                    c3 = c1 + c2;

                }
                else if (type == '-')
                {
                    c3 = c1 - c2;
                }
                else if (type == 'x')
                {
                    c3 = c1 * c2;
                }

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                cout << "                               Question " << i << "/30 :" << endl;
                cout << "                         (";
                c1.print();
                cout << ")" << type << "(";
                c2.print();
                cout << ") = ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                string answer;
                cin >> answer;
                bool right = c3.checkCorrect(answer);
                if (right == true)
                {
                    player1->incAnsRight();
                }
                cout << endl;
            }

            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            int time = chrono::duration_cast<chrono::seconds>(end - begin).count();
            cout << "                            Time taken: " << time << "s" << endl;
            cout << "                          Your score is " << calcScore(player1, time) << endl;
            cout<<"---------------------------------------------------------------------------------"<<endl;
            cout<<endl;
            /**< ---------------------------------------------------------------------------------------------- */

            /**< Decides whether a player loses, wins or draws & displays the message */
            for (int i = 0; i < 10; i++)
            {
                if (player1->getScore() > board.topScores[i])
                {
                    Insert(board.topNames, 10, (i+1), player1->getName());
                    Insert(board.topScores, 10, (i+1), player1->getScore());
                    break;
                }

            }
            /**< ---------------------------------------------------------------------------------------------- */

            delete player1;
        }

        /**< Displays updated leader board */
        cout << endl;
        printBoard(board);

        ofstream outTopNames, outTopScores;
        outTopNames.open("topNames.txt");
        outTopScores.open("topScores.txt");
        if (outTopNames && outTopScores)
        {
            for (int i = 0; i < 9; i++)
            {
                outTopNames << board.topNames[i] << endl;
                outTopScores << board.topScores[i] << endl;
            }
            outTopNames << board.topNames[9];
            outTopScores << board.topScores[9];
        }
        else
        {
            cout << "File/s does not exist." << endl;
        }
        outTopNames.close();
        outTopScores.close();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        cout<<"---------------------------------------------------------------------------------"<<endl;
        cout<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        /**< ---------------------------------------------------------------------------------------------- */

        cout << endl;
        cout << "                         Play again (Y)/(N): ";
        cin >> playAgain;
        cout << endl;
    }
    while ((playAgain == 'Y') || (playAgain == 'y'));

    /**< Displays Credits textfile */
    cout << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout<<"---------------------------------------------------------------------------------"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    printTextfile("Headings//Credits Header.txt");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    printTextfile("Credits.txt");
    cout<<"---------------------------------------------------------------------------------"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    /**< ---------------------------------------------------------------------------------------------- */

    Sleep(1000);//creates a delay in time so that the music plays while the player reads the credits
    t.detach();//ends the thread that was used to play background music

    return 0;
}
/**< ---------------------------------------------------------------------------------------------- */

/**< Calculates the player score */
int calcScore(Player *player, int time)
{
    player->adjustScore(player->getAnsRight()*100);
    player->adjustScore((30 - player->getAnsRight())*-50);
    player->adjustScore(-time);

    return player->getScore();
}

/**< Prints a text file */
void printTextfile(string strFile)
{
    string line;
    ifstream txtfile(strFile);
    if(txtfile.is_open())
    {
        while(getline(txtfile, line))
            cout << line << endl;
        txtfile.close();
    }
    else
        cout << "Unable to open file";
}

/**< Generates a random integer */
int random()
{
    auto start = chrono::steady_clock::now();
    Sleep(1);
    auto end = chrono::steady_clock::now();
    int n = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
    srand(n);
    int num = rand()%21 - 10; // generates a random number from -10 to 10
    return num;
}

/**< Generates a type of operator(+,-,x) for the complex question */
char genType()
{
    auto start = chrono::steady_clock::now();
    Sleep(1);
    auto end = chrono::steady_clock::now();
    int n = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
    srand(n);
    int num = rand()%3 + 1;
    switch (num)
    {
    case 1:
        return '+';
    case 2:
        return '-';
    default:
        return 'x';
    }
}
