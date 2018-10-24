#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <string>
#include "random.hpp"


using namespace std;

int throwDice(int amount, int dice)  {
	int dices = 0;
	for(int i = 0; i<amount; i++)
		dices += randomNo(dice, 1);
	return dices;
}

int main() {
    cout << throwDice(1, 25) << endl;
}