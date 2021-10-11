#include "CellularAutomaton.h"

/**
 * @brief Used for passing data to a thread
 */
typedef struct {
	int			start; // start, end mark the section of the automatons buffer assigned to the current thread
	int			end;
	CellularAutomaton *	automaton;
} ThreadData;

long coreCount;

CellularAutomaton newAutomaton(unsigned int survive[], size_t sSize, unsigned int revive[], size_t rSize, double fillPercent, int width, int height)
{
	// Fetch cpu core count
	coreCount = sysconf(_SC_NPROCESSORS_CONF);
	if (coreCount == -1) { // sysconf failed
		perror("Couldn't determine cpu core count, defaulting to 1");
		coreCount = 1;
	}

	bool *bufferA = malloc(width * height * sizeof(bool));
	bool *bufferB = malloc(width * height * sizeof(bool));

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double rng = rand01();
			if (rng <= fillPercent)
				bufferA[x + y * width] = true;
			else
				bufferA[x + y * width] = false;
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

CellularAutomaton newAutomatonFromArray(bool *array, unsigned int survive[], size_t sSize, unsigned int revive[], size_t rSize, int width, int height)
{
	coreCount = sysconf(_SC_NPROCESSORS_CONF);
	if (coreCount == -1) { // sysconf failed
		perror("Couldn't determine cpu core count, defaulting to 1");
		coreCount = 1;
	}

	bool *bufferA = calloc(width * height, sizeof(bool));
	bool *bufferB = calloc(width * height, sizeof(bool));

	for (int i = 0; i < width * width; i++)
		bufferA[i] = array[i];

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

// Helper, executed for each cell in a thread
void *tickCell(void *data)
{
	ThreadData *tData = (ThreadData *)data;

	for (int i = tData->start; i < tData->end; i++) {
		int x = i % (*(tData->automaton)).width;
		int y = i / (*(tData->automaton)).width;

		unsigned int nbCount = neighbourCount(*(tData->automaton), x, y);

		bool *usedBuffer = currentBuffer(*(tData->automaton));
		bool *otherBuffer = unusedBuffer(*(tData->automaton));

		if (usedBuffer[i]) {
			bool survives = false;
			for (size_t j = 0; j < (*(tData->automaton)).surviveRuleCount; j++) {
				if (nbCount == (*(tData->automaton)).surviveRules[j]) {
					survives = true;
					break;
				}
			}

			otherBuffer[i] = survives;
		} else {
			bool birth = false;
			for (size_t j = 0; j < (*(tData->automaton)).reviveRuleCount; j++) {
				if (nbCount == (*(tData->automaton)).reviveRules[j]) {
					birth = true;
					break;
				}
			}

			otherBuffer[i] = birth;
		}
	}

	free(tData);
	return NULL;
}

void tick(CellularAutomaton *automaton)
{
	pthread_t threads[coreCount];

	int pixelsPerCore = (automaton->width * automaton->height) / coreCount;
	int remainingPixels = (automaton->width * automaton->height) % (pixelsPerCore * coreCount);

	for (int i = 0; i < coreCount; i++) {
		ThreadData *data = malloc(sizeof(ThreadData));

		int start = i * pixelsPerCore;
		int end = start + pixelsPerCore;
		if (i == coreCount - 1)
			end += remainingPixels;

		*data = (ThreadData) { start, end, automaton };

		if (pthread_create(&threads[i], NULL, tickCell, (void *)data) != 0)
			perror("Couldn't create thread:");
	}

	for (int i = 0; i < coreCount; i++)
		if (pthread_join(threads[i], NULL) != 0)
			perror("Couldn't join thread:");

	automaton->currentBufferIdx = !automaton->currentBufferIdx;
}

bool *currentBuffer(CellularAutomaton automaton)
{
	return automaton.buffers[automaton.currentBufferIdx];
}

bool *unusedBuffer(CellularAutomaton automaton)
{
	return automaton.buffers[!automaton.currentBufferIdx];
}

unsigned int neighbourCount(CellularAutomaton automaton, int x, int y)
{
	unsigned int count = 0;

	for (int yoff = -1; yoff <= 1; yoff++) {
		for (int xoff = -1; xoff <= 1; xoff++) {
			if (xoff == 0 && yoff == 0)
				continue;

			int xp = x + xoff;
			int yp = y + yoff;

			if (xp < 0)
				xp = automaton.width - 1;
			else if (xp >= (int)automaton.width)
				xp = 0;

			if (yp < 0)
				yp = automaton.height - 1;
			else if (yp >= (int)automaton.height)
				yp = 0;

			bool *usedBuffer = currentBuffer(automaton);
			if (usedBuffer[xp + yp * automaton.width])
				count++;
		}
	}

	return count;
}

void setCell(CellularAutomaton automaton, int x, int y, bool alive)
{
	bool *usedBuffer = currentBuffer(automaton);

	usedBuffer[x + y * automaton.width] = alive;
}

void print(CellularAutomaton automaton)
{
	bool *usedBuffer = currentBuffer(automaton);

	for (size_t y = 0; y < automaton.height; y++) {
		for (size_t x = 0; x < automaton.width; x++) {
			if (usedBuffer[x + y * automaton.width])
				printf("\u2B1B");
			else
				printf("\u2B1C");
		}
		printf("\n");
	}
}

double rand01()
{
	return (double)rand() / (double)RAND_MAX;
}

void freeAutomaton(CellularAutomaton automaton)
{
	free(automaton.buffers[0]);
	free(automaton.buffers[1]);
}
