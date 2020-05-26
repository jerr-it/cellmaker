#include "CellularAutomaton.h"

CellularAutomaton* createAutomaton(char* rule, double fillPercent, int xDimension, int yDimension)
{
    //Create field and initialize
    CellularAutomaton* automaton = (CellularAutomaton*)calloc(1, sizeof(CellularAutomaton));

    automaton->bufferA = (bool*)calloc(xDimension * yDimension, sizeof(bool));
    automaton->bufferB = (bool*)calloc(xDimension * yDimension, sizeof(bool));

    automaton->usingA = true;

    automaton->xDim = xDimension;
    automaton->yDim = yDimension;

    for (int y = 0; y < automaton->yDim; y++)
    {
        for (int x = 0; x < automaton->xDim; x++)
        {
            double rng = rand01();
            if (rng <= fillPercent)
            {
                automaton->bufferA[x + y * automaton->xDim] = true;
            }
            else
            {
                automaton->bufferA[x + y * automaton->xDim] = false;
            }
        }
    }

    //Read rules
    char delimiter[] = "/";

    //Create survival rules
    char* survivalRule = strtok(rule, delimiter);

    automaton->rulesSurvivalCount = strlen(survivalRule);
    automaton->rulesSurvival      = (int*)calloc(automaton->rulesSurvivalCount, sizeof(int));

    for (int i = 0; i < automaton->rulesSurvivalCount; i++)
    {
        automaton->rulesSurvival[i] = survivalRule[i] - '0';
    }

    //Create birth rules
    char* birthRule = strtok(NULL, delimiter);

    automaton->rulesBirthCount = strlen(birthRule);
    automaton->rulesBirth      = (int*)calloc(automaton->rulesBirthCount, sizeof(int));

    for (int i = 0; i < automaton->rulesBirthCount; i++)
    {
        automaton->rulesBirth[i] = birthRule[i] - '0';
    }

    return(automaton);
}

CellularAutomaton* createAutomatonFromArray(bool* array, char* rule, int xDimension, int yDimension)
{
    //Create field and initialize
    CellularAutomaton* automaton = (CellularAutomaton*)calloc(1, sizeof(CellularAutomaton));

    automaton->bufferA = (bool*)calloc(xDimension * yDimension, sizeof(bool));
    automaton->bufferB = (bool*)calloc(xDimension * yDimension, sizeof(bool));

    automaton->usingA = true;

    automaton->xDim = xDimension;
    automaton->yDim = yDimension;

    for (int i = 0; i < xDimension * yDimension; i++)
    {
        automaton->bufferA[i] = array[i];
    }

    //Read rules
    char delimiter[] = "/";

    //Create survival rules
    char* survivalRule = strtok(rule, delimiter);

    automaton->rulesSurvivalCount = strlen(survivalRule);
    automaton->rulesSurvival      = (int*)calloc(automaton->rulesSurvivalCount, sizeof(int));

    for (int i = 0; i < automaton->rulesSurvivalCount; i++)
    {
        automaton->rulesSurvival[i] = survivalRule[i] - '0';
    }

    //Create birth rules
    char* birthRule = strtok(NULL, delimiter);

    automaton->rulesBirthCount = strlen(birthRule);
    automaton->rulesBirth      = (int*)calloc(automaton->rulesBirthCount, sizeof(int));

    for (int i = 0; i < automaton->rulesBirthCount; i++)
    {
        automaton->rulesBirth[i] = birthRule[i] - '0';
    }

    return(automaton);
}

void tick(CellularAutomaton* automaton)
{
    //Check every spot on current buffer
    for (int y = 0; y < automaton->yDim; y++)
    {
        for (int x = 0; x < automaton->xDim; x++)
        {
            //Apply rules
            int nbCount = getNeighborCount(automaton, x, y);

            bool* currentBuffer = getCurrentBuffer(automaton);
            bool* otherBuffer   = getUnusedBuffer(automaton);

            if (currentBuffer[x + y * automaton->xDim])
            {
                bool survives = false;
                //Loop over survival rules
                for (int i = 0; i < automaton->rulesSurvivalCount; i++)
                {
                    if (nbCount == automaton->rulesSurvival[i])
                    {
                        survives = true;
                        break;
                    }
                }

                otherBuffer[x + y * automaton->xDim] = survives;
            }
            else
            {
                bool birth = false;
                //Loop over birth rules
                for (int i = 0; i < automaton->rulesBirthCount; i++)
                {
                    if (nbCount == automaton->rulesBirth[i])
                    {
                        birth = true;
                        break;
                    }
                }

                otherBuffer[x + y * automaton->xDim] = birth;
            }
        }
    }
    automaton->usingA = !automaton->usingA;
}

bool* getUnusedBuffer(CellularAutomaton* automaton)
{
    if (automaton->usingA)
    {
        return(automaton->bufferB);
    }
    else
    {
        return(automaton->bufferA);
    }
}

bool* getCurrentBuffer(CellularAutomaton* automaton)
{
    if (automaton->usingA)
    {
        return(automaton->bufferA);
    }
    else
    {
        return(automaton->bufferB);
    }
}

int getNeighborCount(CellularAutomaton* automaton, int x, int y)
{
    int count = 0;

    for (int yoff = -1; yoff <= 1; yoff++)
    {
        for (int xoff = -1; xoff <= 1; xoff++)
        {
            if (xoff == 0 && yoff == 0)
            {
                continue;
            }

            int xp = x + xoff;
            int yp = y + yoff;

            //Wrap around
            if (xp < 0)
            {
                xp = automaton->xDim - 1;
            }
            else if (xp >= automaton->xDim)
            {
                xp = 0;
            }

            if (yp < 0)
            {
                yp = automaton->yDim - 1;
            }
            else if (yp >= automaton->yDim)
            {
                yp = 0;
            }

            bool* currentBuffer = getCurrentBuffer(automaton);
            if (currentBuffer[xp + yp * automaton->xDim])
            {
                count++;
            }
        }
    }

    return(count);
}

void setCell(CellularAutomaton* automaton, int x, int y, bool alive)
{
    bool* currentBuffer = getCurrentBuffer(automaton);

    currentBuffer[x + y * automaton->xDim] = alive;
}

void print(CellularAutomaton* automaton)
{
    for (int y = 0; y < automaton->yDim; y++)
    {
        for (int x = 0; x < automaton->xDim; x++)
        {
            bool* currentBuffer = getCurrentBuffer(automaton);
            if (currentBuffer[x + y * automaton->xDim])
            {
                printf("⬛");
            }
            else
            {
                printf("⬜");
            }
        }
        printf("\n");
    }
}

double rand01()
{
    return((double)rand() / (double)RAND_MAX);
}

void freeAutomaton(CellularAutomaton* automaton)
{
    free(automaton->rulesBirth);
    free(automaton->rulesSurvival);
    free(automaton->bufferA);
    free(automaton->bufferB);
    free(automaton);
}
