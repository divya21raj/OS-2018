#include <time.h>
#include <stdlib.h>
#include <bits/types/FILE.h>
#include <libio.h>
#include <stdio.h>
#include <memory.h>
#include <unistd.h>

#include "pageAlgos.h"

int mostRecentlyUsed = 0;

int *initFrames(int size);

void printFrames(int *frameArray, int size);

int *initAge(int size);

void incrementAge(int *age, int frame);

int findLRU(const int *age, int size);

int pageHasFrame(int page, const int *frameArray, int frameSize);

int findOPT(int pageIndex, int *frameArray, int *pageArray, int frameSize, int pageArraySize);


int opt(int *pageArray, int pageArraySize, int frameSize)
{
	int misses = 0;
	int empty = 0;

	int *frameArray = initFrames(frameSize);

	int victimFrame = 0;

	for(int i=0; i< pageArraySize; i++)
	{
		//printf("\n%d. ", pageArray[i]);

		int positionInFrameArray = pageHasFrame(pageArray[i], frameArray, frameSize);
		if(positionInFrameArray == -1)
		{
			//printf("Miss!  ");
			misses++;

			victimFrame = findOPT(i, frameArray, pageArray, frameSize, pageArraySize);

			if(empty < frameSize)
				victimFrame = empty++;

			frameArray[victimFrame] = pageArray[i];
		}

		else
		{
			//printf("Hit!  ");
		}

		//printFrames(frameArray, frameSize);
	}

	return misses;
}

int findOPT(int pageIndex, int *frameArray, int *pageArray, int frameSize, int pageArraySize)
{
	int frameIndex = 0;
	int farthest = pageIndex;

	for(int i=0; i<frameSize; i++)
	{
		if(frameArray[i] == -1)
		{
			frameIndex = i;
			break;
		}

		int j;
		for(j=pageIndex; j<pageArraySize; j++)
		{
			if(pageArray[j] == frameArray[i] && j > farthest)
			{
				farthest = j;
				frameIndex = i;
				break;
			}
		}

		if(j == pageArraySize) //page won't be referenced in future
		{
			frameIndex = i;
			break;
		}
	}

	return frameIndex;
}

int lru(int *pageArray, int pageArraySize, int frameSize)
{
	int misses = 0;

	int *frameArray = initFrames(frameSize);
	int *age = initAge(frameSize);

	int victimFrame = 0;

	for(int i=0; i<pageArraySize; i++)
	{
		//printf("\n%d. ", pageArray[i]);
		int positionInFrameArray = pageHasFrame(pageArray[i], frameArray, frameSize);
		if(positionInFrameArray == -1)
		{
			//printf("Miss!  ");
			misses++;

			victimFrame = findLRU(age, frameSize);
			frameArray[victimFrame] = pageArray[i];
			incrementAge(age, victimFrame);
			mostRecentlyUsed = victimFrame;
		}

		else
		{
			//printf("Hit!  ");
			age[positionInFrameArray] = age[mostRecentlyUsed] + 1;
			mostRecentlyUsed = positionInFrameArray;
		}

		//printFrames(frameArray, frameSize);

	}

	return misses;
}

int findLRU(const int *age, int size)
{
	int index = 0;

	for(int i = 0; i<size; i++)
	{
		if(age[i] < age[index])
			index = i;
	}

	return index;
}

void incrementAge(int *age, int frame)
{
	age[frame] = age[mostRecentlyUsed] + 1;
	mostRecentlyUsed = frame;
}

int *initAge(int size)
{
	int *age = malloc(size * sizeof(int));

	for(int i=0; i<size; i++)
		age[i] = 0;

	return age;
}

int fifo(int *pageArray, int pageArraySize, int frameSize)
{
	int misses = 0;
	int *frameArray = initFrames(frameSize);

	int victimFrame = 0;

	for(int i=0; i<pageArraySize; i++)
	{
		if(pageHasFrame(pageArray[i], frameArray, frameSize) == -1)
		{
			//printf("\n%d. Miss!", pageArray[i]);
			misses++;

			frameArray[victimFrame] = pageArray[i];
			victimFrame = (victimFrame + 1)%frameSize;
		}

		else
		{
			//Hit!
		}
	}

	return misses;
}

int pageHasFrame(int page, const int *frameArray, int frameSize)
{
	int positionInFrameArray = -1;

	for(int i=0; i< frameSize; i++)
	{
		if(frameArray[i] == page)
		{
			positionInFrameArray = i;
			break;
		}
	}

	return positionInFrameArray;
}


void printFrames(int *frameArray, int size)
{
	printf("   ");

	for(int i =0; i<size; i++)
		printf(" %d|", frameArray[i]);

	printf("\n");

}

void generateRandomInput(int size, int range, int *randomArray)
{
	char inputPath[1024];
	unsigned int r;
	char currentDir[1024];

	getcwd(currentDir, sizeof(currentDir));

	strcpy(inputPath, currentDir);
	strcat(inputPath, "/input.txt");   //initialising path to history

	srand((unsigned int) time(0));

	FILE *input = fopen(inputPath, "w");

	for(int i =0; i<size; i++)
	{
		r = (unsigned int) (rand()%range);
		randomArray[i] = r;
		fprintf(input, "%d", r);

		if(i != size-1)
			fprintf(input, ",");
	}

	fprintf(input, "\n");

	fclose(input);
}

int *initFrames(int size)
{
	int *frameArray = malloc(size*(sizeof(int)));

	for(int i=0; i<size; i++)
		frameArray[i] = -1;

	return frameArray;
}

