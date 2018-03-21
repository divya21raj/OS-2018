#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/param.h>
#include <memory.h>
#include <stdlib.h>

#define MAX_PARAMETER_LENGTH 2048

typedef struct
{
	int start;
	int end;
}parameters;

long *masterArray;

void parseArguments(char **argv);

bool isFile(char **argv);

void getListFromFile(FILE *pFILE);

long getSize(FILE *pFILE);

int main(int argc, char* argv[MAX_PARAMETER_LENGTH])
{
	pthread_t sorters[2];

	parseArguments(argv);

	return 0;
}

void parseArguments(char **argv)
{
	if(isFile(argv))
	{
		FILE *source = fopen(argv[1], "r");  //opening the file given as argument
		getListFromFile(source);
	}

}

void getListFromFile(FILE *pFILE)
{
	long fileSize = getSize(pFILE);

	masterArray = malloc(sizeof(long) * ((fileSize/2) + 1));  //divided by 2 to ignore ','

	char *inPutStr = malloc(fileSize);
	char *num;
	int i = 0;

	fgets(inPutStr, fileSize, pFILE);

	num = strtok (inPutStr,",");
	while (num != NULL)
	{
		masterArray[i] = atoi(num);
		printf("%li ", masterArray[i++]);
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