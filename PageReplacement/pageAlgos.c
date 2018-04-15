#include <time.h>
#include <stdlib.h>
#include <bits/types/FILE.h>
#include <libio.h>
#include <stdio.h>
#include <memory.h>
#include <unistd.h>

#include "pageAlgos.h"

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

