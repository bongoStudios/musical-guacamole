#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstdint>
using namespace std;

long long int randomNo (int max, int min) {
    int *p = new int, x;
    uintptr_t a = reinterpret_cast<uintptr_t> (p), b = reinterpret_cast<uintptr_t> (&x);
    srand ((time(NULL) * a)/b);
    return (rand() % ((max-min)+1)) + min;
}
