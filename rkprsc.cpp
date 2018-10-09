#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "random.hpp"
#define WIDTH 30
#define HEIGHT 10 

using namespace std;

int startx = 0;
int starty = 0;

char *choices[] = { 
			"Rock",
			"Paper",
			"Scissors",
			"Exit",
		  };
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

void* getchBool (void *args);

int main () {
WINDOW *menu_win;
	int highlight;
	int choice;
	int c;
	int botChoice;

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
		mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice.");
		refresh();
		print_menu(menu_win, highlight);
		while(1)
		{	
			c = wgetch(menu_win);
			switch(c)
			{	case KEY_UP:
					if(highlight == 1)
						highlight = n_choices;
					else
						--highlight;
					break;
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
		clear();
		if(choice == 4) {
			endwin();
			return 0;
		}
		botChoice = randomNo(3, 1);
		if(botChoice == choice) {	
			printw("Hmm, a draw.");	
		} else if(botChoice == 3) {
			printw("Your opponent chose scissors.");
			if(choice == 2)
				printw("You lost the game, and also x doubloons.");
			else
				printw("You won. Was that luck, or skill?\nYou also get a whopping x doubloons");	
		} else if(botChoice == 2) {
			printw("Your opponent chose paper.");
			if(choice == 1)
				printw("You lost the game, and also x doubloons.");
			else
				printw("You won. Was that luck, or skill?\nYou also get a whopping x doubloons");	
		} else {
			printw("Your opponent chose rock.");
			if(choice == 3)
				printw("You lost the game, and also x doubloons.");
			else
				printw("You won. Was that luck, or skill?\nYou also get a whopping x doubloons");	
		}
		refresh();
    	getch();
	}
	endwin();
	return 0;
}

/*void* getchBool(void *args) {
	bool *hayGetch = (bool*) args;
    getch();
    *hayGetch = true;
} */

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
