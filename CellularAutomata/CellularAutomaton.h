/**
 * @file Main cellular automata file
 *
 * @author Jerrit Gläsker
 * @date 24.05.2020
 *
 * @license MIT-License
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/**
 * @brief Saves data related to the cellular automaton
 */
typedef struct {
	bool *		buffers[2];
	unsigned char	currentBufferIdx;

	size_t		width;
	size_t		height;

	unsigned int *	surviveRules;
	size_t		surviveRuleCount;

	unsigned int *	reviveRules;
	size_t		reviveRuleCount;
}CellularAutomaton;

/**
 * Function creating a new cellular automaton
 * @param  rule       Automaton survival/birth rules, seperated by a single slash
 * @param  width      width
 * @param  height     height
 * @return            pointer to new automaton
 */
CellularAutomaton newAutomaton(unsigned int survive[], size_t sSize, unsigned int revive[], size_t rSize, double fillPercent, int width, int height);

/**
 * Create the field from a given array
 * @param  array      array to construct buffer from
 * @param  rule       automaton rule
 * @param  width      width
 * @param  height     height
 * @return            pointer to new automaton
 */
CellularAutomaton newAutomatonFromArray(bool *array, unsigned int survive[], size_t sSize, unsigned int revive[], size_t rSize, int width, int height);

/**
 * Run automaton for 1 iteration
 * @param automaton automaton to run
 */
void tick(CellularAutomaton *automaton);

/**
 * Function for retrieving the currently used buffer of an automaton
 * @param  automaton automaton
 * @return           automatons currently used buffer
 */
bool *currentBuffer(CellularAutomaton automaton);

/**
 * Function for retrieving the currently unused buffer of an automaton
 * @param  automaton automaton
 * @return           automatons currently unused buffer
 */
bool *unusedBuffer(CellularAutomaton automaton);

/**
 * Get the amount of living neighbors of the specified position.
 * Wraps around the edges
 * @param  automaton automaton
 * @param  x         x position
 * @param  y         y position
 * @return           amount of alive neighbors
 */
unsigned int neighbourCount(CellularAutomaton automaton, int x, int y);

/**
 * Set a cells value
 * @param automaton automaton
 * @param x         x position
 * @param y         y position
 * @param alive     alive or not
 */
void setCell(CellularAutomaton automaton, int x, int y, bool alive);

/**
 * Print automaton to console
 * @param automaton automaton to print
 */
void print(CellularAutomaton automaton);

/**
 * Generate random number between 0 and 1
 * @return 0-1 (inclusive)
 */
double rand01();

/**
 * Free automaton
 * @param automaton automaton to free
 */
void freeAutomaton(CellularAutomaton automaton);

#ifdef __cplusplus
}
#endif
