#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "random.hpp"

using namespace std;

void* getchBool (void *args);

int main () {
    
    int playerDice1 = 0;
    int playerDice2 = 0;
    int machineDice1 = 0;
    int machineDice2 = 0;
    char option;
    cout << "Gonna play some dice, are we? (y/n)" << endl;
    cin >> option;
    if(option == 'n') {
        return 0;
    }
    cout << "The machine's gonna roll some dice now, if you would." << endl;
    machineDice1 = randomNo(6, 1);
    sleep(1);
    machineDice2 = randomNo(6, 1);
    cout << "That's a " << machineDice1 << " and a " << machineDice2 << ", " << machineDice1 + machineDice2 << " in total. Your turn, cowboy." << endl;
    cout << "Press any key to start." << endl;
    cin >> option;
    playerDice1 = randomNo(6, 1);
    sleep(1);
    playerDice2 = randomNo(6, 1);
    cout << "That's a " << machineDice1 << " and a " << machineDice2 << ", " << machineDice1 + machineDice2 << " in total." << endl;
    if(machineDice1 + machineDice2 > playerDice1 + playerDice2) {
        cout << "Seems like you've lost this one, haven't ya, chump? Good luck next time." << endl << "Would you like to try again? (y/n)" << endl;
        cin >> option;
        if(option != 'n')
            return 0;
    }
    else if(machineDice1 + machineDice2 < playerDice1 + playerDice2) {
                cout << "Good job chump, match's yours. Wanna rumble again?" << endl;
                cin >> option;
        if(option != 'n')
            return 0;
    }
    else {
        cout << "Oh? That's a tie, how peculiar. Care for another round?" << endl;
        cin >> option;
        if(option != 'n')
            return 0;
    }
    return 0;
}

/*void* getchBool(void *args) {
	bool *hayGetch = (bool*) args;
    getch();
    *hayGetch = true;
} */