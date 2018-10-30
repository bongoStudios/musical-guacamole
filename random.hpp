#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstdint>
using namespace std;

long long int randomNo (int max, int min) {
    int *p = new int, x;
    int a = reinterpret_cast<int> (p), b = reinterpret_cast<int> (&x);
    srand ((time(NULL) * a)/b);
    return (rand() % ((max-min)+1)) + min;
}
