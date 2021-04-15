<h1 align="center">C-ellularAutomaton</h1>
<p align="center">
    <img src="https://img.shields.io/badge/-Language-blue?style=for-the-badge&logo=c" />
</div>
<br>
<p align="center">
Library for simulation of cellular automata, like Conways Game of Life
</p>

<p align="center">
    <img src="img/one.png" width=100/>
    <img src="img/two.png" width=100/>
    <img src="img/three.png" width=100/>
    <img src="img/four.png" width=100/>
    <img src="img/five.png" width=100/>
</div>

<h2 align="center">How to use</h2>

Compile:
```
cmake .
make celautom
./celautom

or

gcc -o automaton main.c CellularAutomata/CellularAutomaton.h CellularAutomata/CellularAutomaton.c
./automaton
```

Visit main.c for complete file example.

Include:
```c
#include "CellularAutomata/CellularAutomaton.h"
```


Define your rules:
```c
//At what neighbor count will a cell survive the current iteration?
unsigned int survive[] = { 2, 3 };
size_t       sSize     = sizeof(survive) / sizeof(unsigned int);

//At what neighbor count will a cell get revived in the current iteration?
unsigned int revive[] = { 3 };
size_t       rSize    = sizeof(revive) / sizeof(unsigned int);
```

Create from array:
```c
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
 CellularAutomaton autom = newAutomatonFromArray(arr, survive, sSize, revive, rSize, 10, 10);
```

<b>Keep in mind that this wraps around the edges, meaning that e.g. cells at the right edge neighbor the cells on the left edge.</b>

Initialize randomly:
```c
srand(time(NULL));
//0.4 means the area will be alive by 40%
CellularAutomaton autom = newAutomaton(survive, sSize, revive, rSize, 0.4, 20, 20);
```

Run steps:
```c
for (int i = 0; i < 40; i++)
{
    print(autom);
    tick(autom);
    printf("\n");
}
```

<b>Print will print the automaton onto the console. However you can render it however you like by accessing the automatons buffer directly. It's a linear array of bools. Retrieve it by using:;</b>

```c
bool* usedBuffer = currentBuffer(autom);
```

Free memory:
```c
freeAutomaton(autom);
```
