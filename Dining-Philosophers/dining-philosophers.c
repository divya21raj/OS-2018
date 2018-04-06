/*
NAME - DIVYA RAJ
ROLL - 1610110123
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void initStuff(char **argv);

void* philosopherWork(void *philosopherNumberAddress);

unsigned int randomNum(int range);  //returns random number between 1 and range

int N;  //Number of philosophers
int iterations;  //eating iterations = N
//semaphore chopstick[5];

int *timeEating;

int main(int argc, char* argv[2])
{
	initStuff(argv);

	pthread_t **philosophers;

	//starting the program clock
	clock_t begin = clock();

	//start all philosophers
	int i;
	for(i = 0; i< N; i++)
	{
		pthread_create(philosophers[i], NULL, philosopherWork, (void *) &i);
	}

	//ending program clock
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nTotal time elapsed since starting: %lf", time_spent);

	for(i = 0; i<N; i++)
		printf("\nPhilosopher no. %d spent %d seconds eating.", i+1, timeEating[i]);

	return 0;
}

void* philosopherWork(void *philosopherNumberAddress)
{
	int philNum = *(int*)philosopherNumberAddress;

	do
	{
		/*pickupForks(philNum);
		....

		*/
		//eat for a while
	 	printf("\nPhilosopher number %d is eating...", philNum + 1);
	 	iterations--;
	 	unsigned int eatTime = randomNum(3);
	 	sleep(eatTime);
	 	timeEating[philNum] += eatTime;

	 	/*returnForks(philNum);
		. . .

		think for awhile
	 	*/sleep(randomNum(3));
		//. . .

	}
	while (iterations>0);

}

void initStuff(char **argv)
{
	N = atoi(argv[2]);
	iterations = N;

	timeEating = malloc(N* sizeof(int));
	timeEating = {0};

	printf("Number of philosophers = %d", N);
}

unsigned int randomNum(int range)  //returns random number between 1 and range
{
	srand((unsigned int) time(NULL));
	int r = 1 + rand()%range;

	return r;
}