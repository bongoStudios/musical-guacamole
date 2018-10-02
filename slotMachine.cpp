#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include "random.hpp"

string cosos[19] = {
    "ç", "ç", "ç", "ç", "ç", "ç", "ç", "ç",
    "&", "&", "&", "&", "&", "&",
    "¿", "¿", "¿", "¿",
    "7"
};

using namespace std;

int main () {

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    string matriz[3][3];
    int option;
    printw("Welcome to the slot machine bud, good luck!\n");
    printw("So, ye'r going to play? (y/n)\n");
    refresh();
    option = getch();
    if(option == 'n') { 
        endwin();
        return 0;
    }
    int c;
    clear();
    printw("It has begun!\n");
    refresh();
    for(int i= 0; i < 3; i++) { 
        matriz[i][0] = cosos[randomNo(18, 0)];
        matriz[i][1] = cosos[randomNo(18, 0)];
        matriz[i][2] = cosos[randomNo(18, 0)];
        printw("---------------\n");
        printw(" | %s | %s | %s | \n", matriz[i][0].c_str(), matriz[i][1].c_str(), matriz[i][2].c_str());
        refresh();
    }
    printw("---------------\n");
    getch();
    endwin();
    return 0;
}