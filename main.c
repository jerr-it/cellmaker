#include <stdio.h>
#include <time.h>

#include "CellularAutomata/CellularAutomaton.h"

int main()
{
    //https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
    //Rules:
    //Digits before slash tell when a live cell survives this iteration:
    //E.g.: 23/3 means living cells survive if the have either 2 or 3 neighbors, otherwise they die
    //Digits after slash tell when a dead cell becomes alive again:
    //E.g.: 23/3 means a dead cell gets revived if it has exactly 3 neighbors

    srand(time(NULL));
    char rule[] = "23/3";

    bool arr[] =
    {
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
    //CellularAutomaton* autom = createAutomaton(rule, 0.4, 20, 20);
    CellularAutomaton* autom = createAutomatonFromArray(arr, rule, 10, 10);

    for (int i = 0; i < 5; i++)
    {
        print(autom);
        tick(autom);
        printf("\n");
    }

    freeAutomaton(autom);
    return(0);
}
