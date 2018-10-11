#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "random.hpp"

char *userRock[6] = {"    _______", "---'   ____)", "      (_____)", "      (_____)", "      (____)", "---.__(___)"},
*userPaper[6] = {"    _______", "---'   ____)____", "          ______)", "          _______)", "         _______)", "---.__________)"},
*userScissors[6] = {"    _______", "---'   ____)_____", "            _____)", "          ________)", "      (____)", "---.__(___)"},

*machineRock[6] = {"\t  _______", "\t (____   '---", "\t(_____)", "\t(_____)", "\t (____)", "\t  (___)__.---"},
*machinePaper[6] = {"\t       _______", "\t  ____(____   '---", "\t (______", "\t(_______", "\t (_______", "\t   (__________.---"},
*machineScissors[6] = {"\t       _______", "\t  ____(____   '---", "\t (_____", "\t(________", "\t      (____)", "\t       (___)__.---"};

int main() {
    char *temp[6];
	for(int j = 0; j < 6; j++) {
            temp[j] = new char[128];
            cout << "21" << endl;
			strcpy(temp[j], userRock[j]);
            cout << "23" << endl;
			strcat(temp[j], machineRock[j]);
            cout << "25" << endl;
	}
    return 0;
}