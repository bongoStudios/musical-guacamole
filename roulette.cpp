#include <iostream>
#include "random.hpp"
#include <map>
#include <string>

using namespace std;

long long int wallet = randomNo(550, 350);

}
int main() {
    cout << "Welcome, boy, to the House of the Rising Sun." << endl;
    cout << "You have a grand total of " << wallet << " doubloons. What would you like to do with 'em, huh?" << endl;
    while(wallet > 0) {
        char tempChar;
        cout << "Would you like to do sum' bettin' lad? (y/n): ";
        cin >> tempChar;
        if(tempChar == 'n' or tempChar == 'N')
            break;
        cout << "Have a good one!" << endl << endl;
        int optionchosen = 0;
        int bet = 0;
        bool sure = false;
        int option;
        string rb;
        string oe;
        bool colorblack;
        bool odd;
        bool oneeighteen;
        int oneoneeight;
        int twelve;
        int chosen;
        while(bet < 1 && sure && optionchosen > 0) {
            cout << "What would you like bet on: red or black; odd or even; 1st 12, 2nd 12 or 3rd 12; 1-18 or 19-36; or simply a number? ";
            cout << "1 - Red/Black" << endl << "2 - Odd/Even" << endl << "3 - 1st/2nd/3rd 12" << endl << "4 - 1-18/19-36" << endl << "5 - A number" << endl;
            cin >> option;
            switch(option) {
                case 1:
                    cout << "Red or Black?" << endl;
                    cin >> rb;
                if(rb == "red" || rb == "Red") {
                    colorblack = 0;
                    optionchosen = 1;
                    }
                else if(rb == "black" || rb == "Black") {
                        colorblack = 1;
                        optionchosen = 1;
                     }       
                else{
                cout << "Come again?" << endl;
                
                }
                break;
                case 2: 
                cout << "Odd or Even?" << endl;
                cin >> oe;
                if(oe == "odd" || oe == "Odd") {
                odd = 1;
                optionchosen = 2;
                }
                else if(oe == "even" || oe == "Even") {
                odd = 0;
                optionchosen = 2;
                }
                else {
                cout << "Sorry?" << endl;
                break;
                }
                case 3:
                cout << "Wanna bet on the first, second or third 12? (1/2/3)" << endl;
                cin >> twelve;
                if(twelve != 1 && twelve != 2 && twelve != 3) 
                    cout << "Yeah uh, no." << endl;
                    break;
                case 4:
                cout << "Are you going to choose 1 to 18 or 19 to 36?" << endl << "1= (1-18)" << endl << "2- (19-36)" << endl;
                cin >> oneoneeight;
                if (oneoneeight == 1)
                oneeighteen = 1;
                else if (oneoneeight == 1)
                    oneeighteen = 0;
                    else
                    cout << "Um... that's not valid, my guy." << endl;
                    break;
                    case 5:
                    cout << "So, you're gonna choose a number. What will it be?" << endl;
                    cin >> chosen;
                    if(chosen > 36 || chosen < 0)
                    cout << "That ain't how the game works, pal." << endl;
                    break;

    

            }


        }
    }
    cout << "Bye!" << endl;
    return 0;
}