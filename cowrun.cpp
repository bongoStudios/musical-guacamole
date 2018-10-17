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

class Cow {
public:
	Cow (char[24],int,int,int,int);
	int intelligence, dexterity, strength, willpower;
	char name[24];
};
Cow::Cow(char naming[24], int intel, int dext, int stren, int willp) {
	for(int i = 0; i < 24; i++)
		name[i] = naming[i];
	intelligence = intel;
	dexterity = dext;
	strength = stren;
	willpower = willp;
}

class Jockey {
public:
	Jockey (char[24], char[24], int, int);
	int riding, luck;
	char firstName[24], lastName[24];
};
Jockey::Jockey(char nameJ[24], char surnameJ[24], int rideSkill, int luckStat) {

}

char firstNames[][24] = { "Adam", "Alex", "Aaron", "Ben", "Carl", "Dan", "David", "Edward", "Fred", "Frank", "George", "Hal", "Hank", "Ike", "John", "Jack", "Joe", "Larry", "Monte", "Matthew", "Mark", "Nathan", "Otto", "Paul", "Peter", "Roger", "Rosaline", "Steve", "Thomas", "Tim", "Tyler", "Victor", "Walter", "Julian", "Rory", "Maximilian", "Angela", "Dmitri", "Vladimir", "Moriah", "Jebediah", "Viktor", "Jeff", "Timothy", "Jari", "Robin", "Alessandra", "Moe", "Duncan", "Layla", "Lia", "Daniel", "Beatrice", "Bjorn", "Sullivan", "Dorothy", "Joel", "Kenny", "Robert"},
lastNames[][24] = { "Anderson", "Ashwoon", "Aikin", "Bateman", "Bongard", "Bowers", "Boyd", "Cannon", "Cast", "Deitz", "Dewalt", "Ebner", "Frick", "Hancock", "Haworth", "Hesch", "Hoffman", "Kassing", "Knutson", "Lawless", "Lawicki", "Mccord", "McCormack", "Miller", "Myers", "Nugent", "Ortiz", "Orwig", "Ory", "Paiser", "Pak", "Pettigrew", "Quinn", "Quizoz", "Ramachandran", "Resnick", "Sagar", "Schickowski", "Schiebel", "Sellon", "Severson", "Shaffer", "Solberg", "Soloman", "Sonderling", "Soukup", "Soulis", "Stahl", "Sweeney", "Tandy", "Trebil", "Trusela", "Trussel", "Turco", "Uddin", "Uflan", "Ulrich", "Upson", "Vader", "Vail", "Valente", "Van Zandt", "Vanderpoel", "Ventotla", "Vogal", "Wagle", "Wagner", "Wakefield", "Weinstein", "Weiss", "Woo", "Yang", "Yates", "Yocum", "Zeaser", "Zeller", "Ziegler", "Bauer", "Baxster", "Casal", "Cataldi", "Caswell", "Celedon", "Chambers", "Chapman", "Christensen", "Darnell", "Davidson", "Davis", "DeLorenzo", "Dinkins", "Doran", "Dugelman", "Dugan", "Duffman", "Eastman", "Ferro", "Ferry", "Fletcher", "Fietzer", "Hylan", "Hydinger", "Illingsworth", "Ingram", "Irwin", "Jagtap", "Jenson", "Johnson", "Johnsen", "Jones", "Jurgenson", "Kalleg", "Kaskel", "Keller", "Leisinger", "LePage", "Lewis", "Linde", "Lulloff", "Maki", "Martin", "McGinnis", "Mills", "Moody", "Moore", "Napier", "Nelson", "Norquist", "Nuttle", "Olson", "Ostrander", "Reamer", "Reardon", "Reyes", "Rice", "Ripka", "Roberts", "Rogers", "Root", "Sandstrom", "Sawyer", "Schlicht", "Schmitt", "Schwager", "Schutz", "Schuster", "Tapia", "Thompson", "Tiernan", "Tisler" },
cowNames[][24] = { "Becky", "Bessy", "Abby", "Gertrudis", "Bassy", "Danielle", "Prima", "Yeeta", "Julia", "Adrianna", "Caecilia", "Balbina", "Leufelia", "Cornelia", "Lewa" };

char *choices[10] = { 
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
        printw("Calculating stats for new cow race");
    }
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