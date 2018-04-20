/*
 NAME = DIVYA RAJ
 ID = 1610110123 */

#include "pageAlgos.h"

#include <stdio.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMBEROFPAGES 100
#define PAGERANGE 20

int frameSize = 1;

int *pageArray;
int pageArraySize = 0;

void parseArguments(char **argv);

void getListFromFile(FILE *pFILE);

bool isFile(char **argv);

long getSize(FILE *pFILE);

void displayArray(int *array, int size);

void setFrameSize(int i);

void makeTable(int *fifo, int *lru, int *opt);

int main(int argc, char* argv[2])
{
	//arrays that store the various page faults occurring for different frame sizes
	int *pageFaultsFIFO = malloc(4* sizeof(int));
	int *pageFaultsLRU = malloc(4* sizeof(int));
	int *pageFaultsOPT = malloc(4* sizeof(int));

	parseArguments(argv);

	displayArray(pageArray, pageArraySize);

	for(int i = 0; i < 4; i++)
	{
		setFrameSize(i);   //varying the frame size b/w 1, 4, 6, 10

		pageFaultsFIFO[i] = fifo(pageArray, pageArraySize, frameSize);

		pageFaultsLRU[i] = lru(pageArray, pageArraySize, frameSize);

		pageFaultsOPT[i] = opt(pageArray, pageArraySize, frameSize);

	}

	makeTable(pageFaultsFIFO, pageFaultsLRU, pageFaultsOPT);

	return 0;
}

void makeTable(int *fifo, int *lru, int *opt)
{
	printf("\n\t     MISSES OCCURRED         ");
	printf("\n+---------------------------------------+");
	printf("\n|\t|            Frames             |");
	printf("\n|\t|1\t|4\t|6\t|10\t|");
	printf("\n|---------------------------------------|");
	printf("\n|FIFO\t|%d\t|%d\t|%d\t|%d\t|", fifo[0], fifo[1], fifo[2], fifo[3]);
	printf("\n|---------------------------------------|");
	printf("\n|LRU \t|%d\t|%d\t|%d\t|%d\t|", lru[0], lru[1], lru[2], lru[3]);
	printf("\n|---------------------------------------|");
	printf("\n|OPT \t|%d\t|%d\t|%d\t|%d\t|", opt[0], opt[1], opt[2], opt[3]);
	printf("\n+---------------------------------------+\n\n");
}

void setFrameSize(int i)
{
	switch(i)
	{
		case 1:	frameSize = 4;
			break;

		case 2:	frameSize = 6;
			break;

		case 3:	frameSize = 10;
			break;

		default:break;
	}
}

void parseArguments(char **argv)
{
	if(isFile(argv))
	{
		FILE *source = fopen(argv[1], "r");  //opening the file given as argument
		getListFromFile(source);
	}

	else
	{
		pageArraySize = NUMBEROFPAGES;
		pageArray = malloc(sizeof(int) * pageArraySize);

		printf("Input file not found! Creating own...\n");
		generateRandomInput(NUMBEROFPAGES, PAGERANGE, pageArray);
	}
}

void displayArray(int *array, int size)
{
	int i=0;
	printf("Array is as follows...\n");
	for(i = 0; i<size; i++)
	{
		printf("%d", array[i]);

		if(i != size - 1)
			printf(", ");
	}

	printf("\n");
}

void getListFromFile(FILE *pFILE)
{
	long fileSize = getSize(pFILE);
	pageArray = malloc(sizeof(int) * ((fileSize/2) + 1));  //divided by 2 to ignore ','

	char *inPutStr = malloc(fileSize);
	char *num;

	fgets(inPutStr, fileSize, pFILE);

	num = strtok (inPutStr,",");
	while (num != NULL && num != "\n")
	{
		int page = atoi(num);
		pageArray[pageArraySize++] = page;
		num = strtok (NULL, ",");
	}
}

long getSize(FILE *pFILE)
{
	fseek(pFILE, 0L, SEEK_END);
	long size = ftell(pFILE);
	fseek(pFILE, 0L, SEEK_SET);

	return size;
}

bool isFile(char **argv)
{
	return access(argv[1], F_OK) == 0;
}
