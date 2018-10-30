#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "random.hpp"
#define WIDTH 30
#define HEIGHT 10 

using namespace std;

int startx = 0, starty = 0, firstNamesLength = 59,
lastNamesLength = 150, cowNamesLength = 15;


int throwDice(int amount, int dice)  {
	int dices = 0;
	for(int i = 0; i<amount; i++)
		dices += randomNo(dice, 1);
	return dices;
}

struct Cow {
	void declare(char naming[24]) {
		for(int i = 0; i < 24; i++)
			name[i] = naming[i];
		intelligence = randomNo(5, -5);
		dexterity = randomNo(5, -5);
		strength = randomNo(5, -5);
		willpower = randomNo(5, -5);
	}
	int intelligence, dexterity, strength, willpower;
	char name[24];
};

struct Jockey {
	void declare(char nameJ[24], char surNameJ[24]) {
		for(int i = 0; i < 24; i++) {
			firstName[i] = nameJ[i];
			lastName[i] = surNameJ[i];
		}
		riding = randomNo(5, -5);
		luck = randomNo(5, -5);
	}
	int riding, luck, pos = 0;
	char firstName[24], lastName[24];
	Cow cow;
};

struct Event {
	char text[10][384];
	char winText[384];
	char loseText[384];
	int textSize;
	string usedAttribute;
	int *attribute,
	amountOfDices,
	kindOfDice,
	diffClass,
	winPlacement,
	losePlacement;
};

Event events[100];

char firstNames[][24] = { "Adam", "Alex", "Aaron", "Ben", "Carl", "Dan", "David", "Edward", "Fred", "Frank", "George", "Hal", "Hank", "Ike", "John", "Jack", "Joe", "Larry", "Monte", "Matthew", "Mark", "Nathan", "Otto", "Paul", "Peter", "Roger", "Rosaline", "Steve", "Thomas", "Tim", "Tyler", "Victor", "Walter", "Julian", "Rory", "Maximilian", "Angela", "Dmitri", "Vladimir", "Moriah", "Jebediah", "Viktor", "Jeff", "Timothy", "Jari", "Robin", "Alessandra", "Moe", "Duncan", "Layla", "Lia", "Daniel", "Beatrice", "Bjorn", "Sullivan", "Dorothy", "Joel", "Kenny", "Robert"},
lastNames[][24] = { "Anderson", "Ashwoon", "Aikin", "Bateman", "Bongard", "Bowers", "Boyd", "Cannon", "Cast", "Deitz", "Dewalt", "Ebner", "Frick", "Hancock", "Haworth", "Hesch", "Hoffman", "Kassing", "Knutson", "Lawless", "Lawicki", "Mccord", "McCormack", "Miller", "Myers", "Nugent", "Ortiz", "Orwig", "Ory", "Paiser", "Pak", "Pettigrew", "Quinn", "Quizoz", "Ramachandran", "Resnick", "Sagar", "Schickowski", "Schiebel", "Sellon", "Severson", "Shaffer", "Solberg", "Soloman", "Sonderling", "Soukup", "Soulis", "Stahl", "Sweeney", "Tandy", "Trebil", "Trusela", "Trussel", "Turco", "Uddin", "Uflan", "Ulrich", "Upson", "Vader", "Vail", "Valente", "Van Zandt", "Vanderpoel", "Ventotla", "Vogal", "Wagle", "Wagner", "Wakefield", "Weinstein", "Weiss", "Woo", "Yang", "Yates", "Yocum", "Zeaser", "Zeller", "Ziegler", "Bauer", "Baxster", "Casal", "Cataldi", "Caswell", "Celedon", "Chambers", "Chapman", "Christensen", "Darnell", "Davidson", "Davis", "DeLorenzo", "Dinkins", "Doran", "Dugelman", "Dugan", "Duffman", "Eastman", "Ferro", "Ferry", "Fletcher", "Fietzer", "Hylan", "Hydinger", "Illingsworth", "Ingram", "Irwin", "Jagtap", "Jenson", "Johnson", "Johnsen", "Jones", "Jurgenson", "Kalleg", "Kaskel", "Keller", "Leisinger", "LePage", "Lewis", "Linde", "Lulloff", "Maki", "Martin", "McGinnis", "Mills", "Moody", "Moore", "Napier", "Nelson", "Norquist", "Nuttle", "Olson", "Ostrander", "Reamer", "Reardon", "Reyes", "Rice", "Ripka", "Roberts", "Rogers", "Root", "Sandstrom", "Sawyer", "Schlicht", "Schmitt", "Schwager", "Schutz", "Schuster", "Tapia", "Thompson", "Tiernan", "Tisler" },
cowNames[][24] = { "Becky", "Bessy", "Abby", "Gertrudis", "Bassy", "Danielle", "Prima", "Yeeta", "Julia", "Adrianna", "Caecilia", "Balbina", "Leufelia", "Cornelia", "Lewa" };

char *choices[10] = { 
			"Start",
			"Exit",
		  };

int n_choices = 2, amountOfEvents = 0, posChances[] = {0, 0, 1, 1, 2, 2, 3};

void print_menu(WINDOW *menu_win, int highlight);
void makeTheJockey(int &i, Jockey jockeys[5]);
void printMenu(WINDOW *menu_win, int &choice);
void printRoad() {
	move(0,0);
	for(int i = 0; i < 5; i++) {
		printw("----------------------\n");
		printw("%d\n", i+1);
		printw("%d\n", i+1);
	}

	printw("----------------------\n");
	for(int i = 0; i < 16; i++)
		mvprintw(i, 22, "|");
}
void printPos(Jockey jockeys[5]) {
	for(int i = 0, j = 1; i<5; i++, j+=3) {
		Jockey *current = &jockeys[i];
		mvprintw(j, 2+(*current).pos, "_");
	}
}
void loadEvents();
void cleanChoices() {
	for(int i = 0; i < 10; i++)
		choices[i] = "";
}
int strToInt(string temp);
int attributeToInt(string attr, Jockey jockey);

int main () {
    WINDOW *menu_win;
	int c, choice;
	loadEvents();

    initscr();
	clear();
	noecho();
	cbreak();

	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
		
	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);

    while(1) {
	    Jockey jockeys[5];
		int i = 0;
		clear();
		mvprintw(0, 0, "Calculating stats for the new cow race");
		refresh();
		makeTheJockey(i, jockeys);
		printw(".");
		refresh();
		makeTheJockey(i, jockeys);
		printw(".");
		refresh();
		makeTheJockey(i, jockeys);	
		printw(". ");
		refresh();
		makeTheJockey(i, jockeys);
		makeTheJockey(i, jockeys);
		printw("done\n");
		refresh();
		cleanChoices();
		choices[0] = "Start", choices[1] = "Exit", n_choices = 2;
		printMenu(menu_win, choice);
		if(choice == 2) {
			endwin();
			return 0;
		}
		clear();
		mvprintw(0, 0, "How fortunate, let's bet then. Who you choosin'?");
		cleanChoices();
		n_choices = 5;
		for(int i = 0; i < n_choices; i++) {
			Jockey current = jockeys[i];
			char *str = new char[79];
			strcpy(str, current.lastName);
			strcat(str, " - ");
			strcat(str, current.cow.name);
			choices[i] = str;
		}
		printMenu(menu_win, choice);
		c = 110;
		while(true) {
			clear();
			Jockey current = jockeys[choice-1];
			mvprintw(0, 0, "Jockey:\n\tFirst Name: %s\n\tLast Name: %s\n", current.firstName, current.lastName);
			printw("Cow:\n\tName: %s\n", current.cow.name);
			printw("Are you sure about this? (y/n):");
			refresh();
			c = getch();
			if(c == 121 or c == 89)
				break;
			clear();
			mvprintw(0, 0, "Oh, ok then, Who you choosin'?");
			printMenu(menu_win, choice);
		}
		int theNumberOne = choice;
		clear();
		printRoad();
		printPos(jockeys);
		refresh();
		mvprintw(17, 0, "The one you chose is in line %d\nBegin? (press something)", theNumberOne);
		getch();
		bool kill = false;
		while(true) {
			clear();
			printRoad();
			printPos(jockeys);
			refresh();
			move(17, 0);
			for(int i = 0; i<5; i++) {
				Jockey *current = &jockeys[i];
				if((*current).pos > 19) {
					kill = true;
					printw("In line %d, %s and %s won!\n", i+1, (*current).lastName, (*current).cow.name);
					refresh();
					getch();
				}
			}
			if(kill)
				break;
			for(int i = 0; i<5; i++) {
				Jockey *current = &jockeys[i];
				if(randomNo(100, 1) < 15) {
					Event event = events[randomNo(amountOfEvents-1, 0)];
					int attr = attributeToInt(event.usedAttribute, *current);
					if(theNumberOne == (i+1)) {
						sleep(1);
						clear();
						for(int j = 0; j<event.textSize; j++) {
							printw("%s\n", event.text[j]);
							refresh();
							getch();
						}
						printw("Rolling... ");
						refresh();
						sleep(1);
						int diceRes = throwDice(event.amountOfDices, event.kindOfDice) + attr;
						printw("(%dd%d+%s = %d) < %d = %s\n", event.amountOfDices, event.kindOfDice, event.usedAttribute.c_str(), diceRes, event.diffClass, diceRes < event.diffClass ? "true" : "false");
						refresh();
						getch();
						if(diceRes < event.diffClass) {
							printw("%s\n", event.loseText);
							refresh();
							getch();
							printw("Move %d spaces", event.losePlacement);
							refresh();
							getch();
							(*current).pos += event.losePlacement;
						} else {
							printw("%s\n", event.winText);
							refresh();
							getch();
							printw("Move %d spaces", event.winPlacement);
							refresh();
							getch();
							(*current).pos += event.winPlacement;
						}
					} else {
						int diceRes = throwDice(event.amountOfDices, event.kindOfDice) + attr;
						if(diceRes < event.diffClass)
							(*current).pos += event.losePlacement;
						else
							(*current).pos += event.winPlacement;
					}
					if((*current).pos < 1)
						(*current).pos = 0;
				} else {
					(*current).pos+=posChances[randomNo(6, 0)];
				}
			}
			sleep(2);
		}
		wclear(menu_win);
		
	}
	endwin();
    return 0;
}

void makeTheJockey(int &i, Jockey jockeys[5]) {
	jockeys[i].declare(firstNames[randomNo(firstNamesLength - 1, 0)], lastNames[randomNo(lastNamesLength - 1, 0)]);
	jockeys[i].cow.declare(cowNames[randomNo(cowNamesLength - 1, 0)]);
	i++;
}

void printMenu(WINDOW *menu_win, int &choice) {
	choice = 0;
	int c, highlight = 1;
	refresh();
	print_menu(menu_win, highlight);
	while(1) {	
			c = wgetch(menu_win);
			switch(c) {	
				case 87: case 119: case KEY_UP:
					if(highlight == 1)
						highlight = n_choices;
					else
						--highlight;
					break;
				case 83: case 115: case KEY_DOWN:
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

int strToInt(string temp) {
	return stoi(temp, nullptr, 10);
}

int attributeToInt(string attr, Jockey jockey) {
	switch(attr[0]) {
		case 'i':
			return jockey.cow.intelligence;
		case 'd':
			return jockey.cow.dexterity;
		case 's':
			return jockey.cow.strength;
		case 'w':
			return jockey.cow.willpower;
		case 'r':
			return jockey.riding;
		case 'l':
			return jockey.luck;
	}
	return 1000;
}

void loadEvents() {
	string line;
	int j = 0;
	fstream file;
	file.open("events.txt", ios::in);
	if(!file.is_open())
		return;
	while(!file.eof()) {
		Event *event = &events[j];
		for(int i = 0; i<19; i++) {
			getline(file, line);
			switch(i) {
				case 10:
					strcpy((*event).winText, line.c_str());
					break;
				case 11:
					strcpy((*event).loseText, line.c_str());
					break;
				case 12:
					(*event).textSize = strToInt(line);
					break;
				case 13:
					(*event).usedAttribute = line;
					break;
				case 14:
					(*event).amountOfDices = strToInt(line);
					break;
				case 15:
					(*event).kindOfDice = strToInt(line);
					break;
				case 16:
					(*event).diffClass = strToInt(line);
					break;
				case 17: 
					(*event).losePlacement = strToInt(line);
					break;
				case 18:
					(*event).winPlacement = strToInt(line);
					break;
				default:
					strcpy((*event).text[i], line.c_str());
					break;
			}
		}
		j++;
	}
	amountOfEvents = j;
	file.close();
}