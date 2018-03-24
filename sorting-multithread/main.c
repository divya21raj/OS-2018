#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/param.h>
#include <memory.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_PARAMETER_LENGTH 2048

typedef struct
{
	int start;
	int end;
}parameters;

long *masterArray;
long *sortedArray;

int masterArraySize = 0;
int arrayMiddle;
long fileSize;

void parseArguments(char **argv);

bool isFile(char **argv);

void getListFromFile(FILE *pFILE);

long getSize(FILE *pFILE);

int partition (long *arr, int low, int high);

void swap(long *a, long *b);

void quickSort(int low, int high);

void displayArray(long *array, int low, int high);

void* sortInterface(void *parameter);

void* mergeArrays(void* arg)
;

int main(int argc, char* argv[MAX_PARAMETER_LENGTH])
{
	pthread_t leftSorter, rightSorter, merger;

	parseArguments(argv);

	arrayMiddle = masterArraySize/2;

	printf("\nArray before sorting...\n");
	displayArray(masterArray, 0, masterArraySize);

	//prepare params
	parameters *left = malloc(sizeof(parameters));
	left -> start = 0;
	left -> end = arrayMiddle;

	parameters *right = malloc(sizeof(parameters));
	right -> start = arrayMiddle + 1;
	right -> end = masterArraySize;

	//start sorters
	pthread_create(&leftSorter, NULL, sortInterface, (void*)left);
	pthread_create(&rightSorter, NULL, sortInterface, (void*)right);

	//wait for sorters to finish
	pthread_join(leftSorter, NULL);
	pthread_join(rightSorter, NULL);

	printf("\nLeft thread sorted:\n");
	displayArray(masterArray, left->start, left->end);

	printf("\nRight thread sorted:\n");
	displayArray(masterArray, right->start, right->end);

	//merge sorted halves
	pthread_create(&merger, NULL, mergeArrays, (void*)&arrayMiddle);

	pthread_join(merger, NULL);

	printf("\nMerged and sorted array:\n");
	displayArray(sortedArray, 0, masterArraySize);
	return 0;
}

void* mergeArrays(void* arg)
{
	int middle = *(int*) arg;
	int size1 = middle;
	int size2 = masterArraySize - middle;

	int rightArrayStart = middle + 1;

	sortedArray = malloc(sizeof(long) * ((fileSize/2) + 1));

	int i =0, j = 0, k = 0;  //indices to traverse arrays

	while(i <= size1 && j <= size2)
	{
		if(masterArray[i] < masterArray[rightArrayStart + j])
			sortedArray[k++] = masterArray[i++];

		else
			sortedArray[k++] = masterArray[rightArrayStart + j++];
	}

	while(i < size1)
		sortedArray[k++] = masterArray[i++];

	while(j < size2)
	{
		sortedArray[k++] = masterArray[rightArrayStart + j++];
	}

}

void* sortInterface(void *parameter)
{
	parameters *param = (parameters*)parameter;
	int low = (*param).start;
	int high = (*param).end;

	quickSort(low, high);
}

void displayArray(long *array, int low, int high)
{
	for(int i = low; i <= high; i++)
	{
		printf("%li", array[i]);

		if(i != high)
			printf(", ");
		else
			printf("\n");
	}
}

void quickSort(int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, masterArray[p] is now
		   at right place */
		int pi = partition(masterArray, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}
}

int partition (long *arr, int low, int high)
{
	long pivot = arr[high];    // pivot
	int i = (low - 1);  // Index of smaller element

	for (int j = low; j <= high- 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (arr[j] <= pivot)
		{
			i++;    // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);

	return (i + 1);
}

// A utility function to swap two elements
void swap(long *a, long *b)
{
	long t = *a;
	*a = *b;
	*b = t;
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
	fileSize = getSize(pFILE);

	masterArray = malloc(sizeof(long) * ((fileSize/2) + 1));  //divided by 2 to ignore ','

	char *inPutStr = malloc(fileSize);
	char *num;

	fgets(inPutStr, fileSize, pFILE);

	num = strtok (inPutStr,",");
	while (num != NULL && num != "\n")
	{
		masterArray[masterArraySize++] = atoi(num);
		num = strtok (NULL, ",");
	}
	masterArraySize--;
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