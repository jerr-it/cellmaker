#include <stdio.h>
#include <time.h>

#include "CellularAutomata/CellularAutomaton.h"

int main() {
    srand(time(NULL));

    bool arr[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 1, 1, 0, 1, 0, 0,
        0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 1, 1, 0, 1, 0, 0,
        0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    unsigned int survive[] = { 2, 3 };
    size_t       sSize     = sizeof(survive) / sizeof(unsigned int);

    unsigned int revive[] = { 3 };
    size_t       rSize    = sizeof(revive) / sizeof(unsigned int);

    //CellularAutomaton autom = newAutomaton(survive, sSize, revive, rSize, 0.4, 20, 20);
    CellularAutomaton autom = newAutomatonFromArray(arr, survive, sSize, revive, rSize, 10, 10);

    for (int i = 0; i < 10; i++) {
        print(autom);
        tick(&autom);
        printf("\n");
    }

    freeAutomaton(autom);
    return 0;
}
