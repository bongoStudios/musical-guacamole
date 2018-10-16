#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *userRock[6] = {"    _______", "---'   ____)", "      (_____)", "      (_____)", "      (____)", "---.__(___)"},
*userPaper[6] = {"    _______", "---'   ____)____", "          ______)", "          _______)", "         _______)", "---.__________)"},
*userScissors[6] = {"    _______", "---'   ____)_____", "            _____)", "          ________)", "      (____)", "---.__(___)"},

*machineRock[6] = {"\t  _______", "\t (____   '---", "\t(_____)", "\t(_____)", "\t (____)", "\t  (___)__.---"},
*machinePaper[6] = {"\t       _______", "\t  ____(____   '---", "\t (______", "\t(_______", "\t (_______", "\t   (__________.---"},
*machineScissors[6] = {"\t       _______", "\t  ____(____   '---", "\t (_____", "\t(________", "\t      (____)", "\t       (___)__.---"};

using namespace std;

int main() {
    initscr();
    noecho();
    keypad(stdscr, true);

    char temp[] = "    _______";
    printw(temp);
    refresh();
    getch();
    endwin();
    return 0;
}