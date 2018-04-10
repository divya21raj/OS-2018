/*
NAME - DIVYA RAJ
ROLL - 1610110123
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void initStuff(char **argv);

unsigned int randomNum(int range);  //returns random number between 1 and range

void* philosopherWork(int philNum);

int N;  //Number of philosophers

pthread_mutex_t chopstick[5];

int *timeEating;

int main(int argc, char* argv[])
{
	initStuff(argv);

	pthread_t *philosophers = malloc(N* sizeof(pthread_t));

	//starting the program clock
	clock_t begin = clock();

	int i;
	//initiate all chopstick mutex locks
	for(i=0; i< N; i++)
		pthread_mutex_init(&chopstick[i],NULL);

	//start all philosophers
	for(i = 0; i< N; i++)
		pthread_create(&(philosophers[i]), NULL, (void *)philosopherWork, (void *) i);

	//waiting for all philosopher threads to join
	for(i = 0; i< N; i++)
		pthread_join(philosophers[i], NULL);

	//destroy all chopstick mutex locks
	for(i=0; i< N; i++)
		pthread_mutex_destroy(&chopstick[i]);

	//ending program clock
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nTotal time elapsed since starting: %lf", time_spent);

	for(i = 0; i<N; i++)
		printf("\nPhilosopher no. %d spent %d seconds eating.", i+1, timeEating[i]);

	return 0;
}

void* philosopherWork(int philNum)
{
	//pickup forks
	pthread_mutex_lock(&chopstick[philNum]);
	printf("\nPhilosopher number %d picked up fork number %d", philNum + 1, philNum +1);
	pthread_mutex_lock(&chopstick[(philNum+1)%N]);
	printf("\nPhilosopher number %d picked up fork number %d", philNum + 1, (philNum +1)%5 + 1);

	//eat for a while
	printf("\nPhilosopher number %d is eating...", philNum + 1);
	unsigned int eatTime = randomNum(3);
	sleep(eatTime);
	/*iterations--;
	printf("\t%d", iterations);*/
	timeEating[philNum] += eatTime;

	//return forks
	pthread_mutex_unlock(&chopstick[philNum]);
	printf("\nPhilosopher number %d put down fork number %d", philNum + 1, philNum +1);
	pthread_mutex_unlock(&chopstick[(philNum+1)%N]);
	printf("\nPhilosopher number %d put down fork number %d", philNum + 1, (philNum + 1)%5 +1);

	//think for awhile
	printf("\nPhilosopher number %d is thinking.", philNum + 1);
	sleep(randomNum(3));

}

void initStuff(char **argv)
{
	N = atoi(argv[1]);

	timeEating = (int*) calloc(N, sizeof(int));

	srand((unsigned int) time(0));  //seeding the random no. generator with current time

	printf("Number of philosophers = %d", N);
}

unsigned int randomNum(int range)  //returns random number between 1 and range
{
	unsigned int r = (unsigned int) (1 + rand() % range);

	return r;
}