#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "random.hpp"
#define WIDTH 30
#define HEIGHT 10 

using namespace std;

int startx = 0;
int starty = 0;

string userRock[6] = {"    _______", "---'   ____)", "      (_____)", "      (_____)", "      (____)", "---.__(___)"},
userPaper[6] = {"    _______", "---'   ____)____", "          ______)", "          _______)", "         _______)", "---.__________)"},
userScissors[6] = {"    _______", "---'   ____)_____", "            _____)", "          ________)", "      (____)", "---.__(___)"},

machineRock[6] = {"  _______", " (____   '---", "(_____)", "(_____)", " (____)", "  (___)__.---"},
machinePaper[6] = {"       _______", "  ____(____   '---", " (______", "(_______", " (_______", "   (__________.---"},
machineScissors[6] = {"       _______", "  ____(____   '---", " (_____", "(________", "      (____)", "       (___)__.---"};

string *userChoices[3] = {userRock, userPaper, userScissors},
*machineChoices[3] = {machineRock, machinePaper, machineScissors};

char whatChoice[3][12] = {"Rock!", "Paper!", "Scissors!"},
*choices[5] = { 
			"Rock",
			"Paper",
			"Scissors",
			"Exit",
		  };
		  
int n_choices = 4;

void print_menu(WINDOW *menu_win, int highlight);

int main () {
WINDOW *menu_win;
	int highlight;
	int choice;
	int c;
	int botChoice;
	bool first = true;

	initscr();
	clear();
	noecho();
	cbreak();

	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
		
	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	while(1) {
		choice = 0;
		highlight = 1;
		clear();
		mvprintw(0, 0, "Use arrow keys (or W,S) to go up and down, Press enter to choose.");
		refresh();
		print_menu(menu_win, highlight);
		while(1)
		{	
			c = wgetch(menu_win);
			switch(c)
			{	
				case 87:
				case 119:
				case KEY_UP:
					if(highlight == 1)
						highlight = n_choices;
					else
						--highlight;
					break;
				case 83:
				case 115:
				case KEY_DOWN:
					if(highlight == n_choices)
						highlight = 1;
					else 
						++highlight;
					break;
				case 10:
					choice = highlight;
					break;
			}
			print_menu(menu_win, highlight);
			if(choice != 0)
				break;
		}
		if(first) {
			if(choice == 4) {
				endwin();
				return 0;
			}
			first = false;
			n_choices = 5;
			choices[4] = "Exit";
			choices[3] = "Enhanced version pls";
		}
		if(choice > 3) {
			endwin();
			if(choice == 4)
				1+1;
			return 0;
		}
		for(int i = 0; i < 3; i++) {
			clear();
			for(int j = 0; j < 6; j++) {
				mvprintw(0, 0, whatChoice[i]);
				mvprintw(0, 25, whatChoice[i]);
				mvprintw(j+1, 0, userRock[j].c_str());
				mvprintw(j+1, 25, machineRock[j].c_str());
			}
			refresh();
			usleep(200000);
			clear();
			for(int j = 0; j < 6; j++) {
				mvprintw(0, 0, whatChoice[i]);
				mvprintw(0, 25, whatChoice[i]);
				mvprintw(j+3, 0, userRock[j].c_str());
				mvprintw(j+3, 25, machineRock[j].c_str());
			}
			refresh();
			usleep(200000);
		}
		usleep(100000);
		clear();
		botChoice = randomNo(3, 1);
		for(int i = 0; i < 6; i++) {
			mvprintw(0, 0, whatChoice[choice-1]);
			mvprintw(0, 25, whatChoice[botChoice-1]);
			mvprintw(i+1, 0, userChoices[choice-1][i].c_str());
			mvprintw(i+1, 25, machineChoices[botChoice-1][i].c_str());
		}
		refresh();
		if(botChoice == choice) {	
			mvprintw(10, 0, "Hmm, a draw.");	
		} else if(botChoice == 3) {
			mvprintw(10, 0, "Your opponent chose scissors. ");
			if(choice == 2)
				printw("You lost the game, and also x doubloons.");
			else
				printw("You won. Was that luck, or skill?\nYou also get the whopping amount of x doubloons");	
		} else if(botChoice == 2) {
			mvprintw(10, 0, "Your opponent chose paper. ");
			if(choice == 1)
				printw("You lost the game, and also x doubloons.");
			else
				printw("You won. Was that luck, or skill?\nYou also get the whopping amount of x doubloons");	
		} else {
			mvprintw(10, 0, "Your opponent chose rock. ");
			if(choice == 3)
				printw("You lost the game, and also x doubloons.");
			else
				printw("You won. Was that luck, or skill?\nYou also get the whopping amount of x doubloons");	
		}
		refresh();
		sleep(2);
    	getch();
	}
	endwin();
	return 0;
}

void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1)
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}
