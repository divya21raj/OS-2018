/*
 NAME = DIVYA RAJ
 ID = 1610110123 */

#include "pageAlgos.h"

#include <stdio.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMBEROFPAGES 10
#define PAGERANGE 20

int *pageArray;
int pageArraySize = 0;

void parseArguments(char **argv);

void getListFromFile(FILE *pFILE);

bool isFile(char **argv);

long getSize(FILE *pFILE);

void displayArray(int *array, int size);


int main(int argc, char* argv[2])
{
	parseArguments(argv);

	displayArray(pageArray, pageArraySize);

	return 0;
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
