/**
 * @file Main cellular automata file
 *
 * @author Jerrit Gläsker
 * @date 24.05.2020
 *
 * @license MIT-License
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    bool* bufferA;
    bool* bufferB;
    bool  usingA;

    int   xDim;
    int   yDim;

    int*  rulesSurvival;
    int   rulesSurvivalCount;
    int*  rulesBirth;
    int   rulesBirthCount;
}CellularAutomaton;

/**
 * Function creating a new cellular automaton
 * @param  rule       Automaton survival/birth rules, seperated by a single slash
 * @param  xDimension width
 * @param  yDimension height
 * @return            pointer to new automaton
 */
CellularAutomaton* createAutomaton(char* rule, double fillPercent, int xDimension, int yDimension);

/**
 * Create the field from a given array
 * @param  array      array to construct buffer from
 * @param  rule       automaton rule
 * @param  xDimension width
 * @param  yDimension height
 * @return            pointer to new automaton
 */
CellularAutomaton* createAutomatonFromArray(bool* array, char* rule, int xDimension, int yDimension);

/**
 * Run automaton for 1 iteration
 * @param automaton automaton to run
 */
void tick(CellularAutomaton* automaton);

/**
 * Get the amount of living neighbors of the specified position.
 * Wraps around the edges
 * @param  automaton automaton
 * @param  x         x position
 * @param  y         y position
 * @return           amount of alive neighbors
 */
int getNeighborCount(CellularAutomaton* automaton, int x, int y);

/**
 * Set a cells value
 * @param automaton automaton
 * @param x         x position
 * @param y         y position
 * @param alive     alive or not
 */
void setCell(CellularAutomaton* automaton, int x, int y, bool alive);

/**
 * Print automaton to console
 * @param automaton automaton to print
 */
void print(CellularAutomaton* automaton);

/**
 * Generate random number between 0 and 1
 * @return 0-1 (inclusive)
 */
double rand01();

/**
 * Free automaton
 * @param automaton automaton to free
 */
void freeAutomaton(CellularAutomaton* automaton);
