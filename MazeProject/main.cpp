#include <iostream>
#include "Maze.h"

using namespace std;

int main() {

    int alg, seed;

    cout << "Which algorithm would you like to use?\nEnter 1 for Kruskal's\nEnter literally anything else for Prim's" << endl;
    cin >> alg;
    cout << "\nEnter your seed" << endl;
    cin >> seed;

    //Change size to 30 for final test
    //10 just fits well in the window
    Maze myMaze(30, seed, alg);
    myMaze.Print();

    int bonus;
    cout << endl << endl;
    cout << "Do you wish to generate a list of seeds with path's of increasing magnitude?\nEnter 1 for Yes or any other number for No." << endl;
    cout << "**WARNING**\nTHIS WILL NOT STOP UNLESS YOU GET REALLY LUCKY" << endl;
    cin >> bonus;

    if (bonus == 1) {
        int pathSize = 0;
        int randomSeed;
        int currSize = 0;
        srand(seed);
        while (pathSize < 400) {
            randomSeed = rand();
            Maze myMazeBonus(30, randomSeed, alg);
            pathSize = myMazeBonus.getPathSize();
            if (pathSize > currSize) {
                currSize = pathSize;
                cout << currSize << "\n" << randomSeed << endl;
            }
            if (pathSize >= 400) {
                myMazeBonus.Print();
                break;
            }
        }
        cout << "Wow! You broke 400!\nSeed is: " << randomSeed << endl;
    }


    return 0;
}