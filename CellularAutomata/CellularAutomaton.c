#include "CellularAutomaton.h"

CellularAutomaton newAutomaton(unsigned int survive[], size_t sSize, unsigned int revive[], size_t rSize, double fillPercent, int width, int height) {
    bool* bufferA = calloc(width * height, sizeof(bool));
    bool* bufferB = calloc(width * height, sizeof(bool));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double rng = rand01();
            if (rng <= fillPercent) {
                bufferA[x + y * width] = true;
            } else {
                bufferA[x + y * width] = false;
            }
        }
    }

    return
        (CellularAutomaton) {
            { bufferA, bufferB },
            0,
            width,
            height,
            survive,
            sSize,
            revive,
            rSize,
        };
}

CellularAutomaton newAutomatonFromArray(bool* array, unsigned int survive[], size_t sSize, unsigned int revive[], size_t rSize, int width, int height) {
    bool* bufferA = calloc(width * height, sizeof(bool));
    bool* bufferB = calloc(width * height, sizeof(bool));

    for (int i = 0; i < width * width; i++) {
        bufferA[i] = array[i];
    }

    return
        (CellularAutomaton) {
            { bufferA, bufferB },
            0,
            width,
            height,
            survive,
            sSize,
            revive,
            rSize
        };
}

void tick(CellularAutomaton* automaton) {
    for (int y = 0; y < automaton->height; y++) {
        for (int x = 0; x < automaton->width; x++) {
            int nbCount = neighbourCount(*automaton, x, y);

            bool* usedBuffer  = currentBuffer(*automaton);
            bool* otherBuffer = unusedBuffer(*automaton);

            if (usedBuffer[x + y * (*automaton).width]) {
                bool survives = false;
                for (int i = 0; i < (*automaton).surviveRuleCount; i++) {
                    if (nbCount == (*automaton).surviveRules[i]) {
                        survives = true;
                        break;
                    }
                }

                otherBuffer[x + y * (*automaton).width] = survives;
            } else {
                bool birth = false;
                for (int i = 0; i < (*automaton).reviveRuleCount; i++) {
                    if (nbCount == (*automaton).reviveRules[i]) {
                        birth = true;
                        break;
                    }
                }

                otherBuffer[x + y * (*automaton).width] = birth;
            }
        }
    }
    automaton->currentBufferIdx = !automaton->currentBufferIdx;
}

bool* currentBuffer(CellularAutomaton automaton) {
    return automaton.buffers[automaton.currentBufferIdx];
}

bool* unusedBuffer(CellularAutomaton automaton) {
    return automaton.buffers[!automaton.currentBufferIdx];
}

int neighbourCount(CellularAutomaton automaton, int x, int y) {
    int count = 0;

    for (int yoff = -1; yoff <= 1; yoff++) {
        for (int xoff = -1; xoff <= 1; xoff++) {
            if (xoff == 0 && yoff == 0) {
                continue;
            }

            int xp = x + xoff;
            int yp = y + yoff;

            if (xp < 0) {
                xp = automaton.width - 1;
            } else if (xp >= automaton.width) {
                xp = 0;
            }

            if (yp < 0) {
                yp = automaton.height - 1;
            } else if (yp >= automaton.height) {
                yp = 0;
            }

            bool* usedBuffer = currentBuffer(automaton);
            if (usedBuffer[xp + yp * automaton.width]) {
                count++;
            }
        }
    }

    return count;
}

void setCell(CellularAutomaton automaton, int x, int y, bool alive) {
    bool* usedBuffer = currentBuffer(automaton);

    usedBuffer[x + y * automaton.width] = alive;
}

void print(CellularAutomaton automaton) {
    bool* usedBuffer = currentBuffer(automaton);

    for (int y = 0; y < automaton.height; y++) {
        for (int x = 0; x < automaton.width; x++) {
            if (usedBuffer[x + y * automaton.width]) {
                printf("\u2B1B");
            } else {
                printf("\u2B1C");
            }
        }
        printf("\n");
    }
}

double rand01() {
    return (double)rand() / (double)RAND_MAX;
}

void freeAutomaton(CellularAutomaton automaton) {
    free(automaton.buffers[0]);
    free(automaton.buffers[1]);
}
