#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "random.hpp"

string cosos[19] = {
    "ç", "ç", "ç", "ç", "ç", "ç", "ç", "ç", //x1.5
    "&", "&", "&", "&", "&", "&", //x2
    "¿", "¿", "¿", "¿", //x4
    "7" //x16
};

using namespace std;

void* getchBool (void *args);

int main () {

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    string matriz[3][3];
    int option;
    bool hayInput = false;
    pthread_t thread;
    printw("Welcome to the slot machine bud, good luck!\n");
    printw("So, ye'r going to play? (y/n)\n");
    refresh();
    option = getch();
    if(option == 'n') { 
        endwin();
        return 0;
    }
    int c;
    printw("It has begun!\n");
    refresh();
    getch();
    for(int i= 0; i < 3; i++) {
        for(int j = 0; j<3; j++) {
            matriz[i][j] = cosos[randomNo(18, 0)];
        }
    }

    while(true) {
        pthread_create(&thread, nullptr, getchBool, &hayInput);
        while(!hayInput) {
            clear();
            usleep(100000);
            for(int i = 0; i < 3; i++) {
                string temp = matriz[1][i];
                matriz[1][i] = matriz[0][i];
                matriz[2][i] = temp;
                matriz[0][i] = cosos[randomNo(18, 0)];
            }
            for(int i= 0; i < 3; i++) { 
                printw("---------------\n");
                printw(" | %s | %s | %s | \n", matriz[i][0].c_str(), matriz[i][1].c_str(), matriz[i][2].c_str());
            }
            printw("---------------\n");
            refresh();
        }
        hayInput=false;
        mvprintw(7, 0,"Play again? (y/n)");
        option = getch();
        if(option == 'n') { 
            endwin();
            return 0;
        }
        
    }
    endwin();
    return 0;
}

void* getchBool(void *args) {
	bool *hayGetch = (bool*) args;
    getch();
    *hayGetch = true;
}