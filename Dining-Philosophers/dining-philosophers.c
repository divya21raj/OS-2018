/*
NAME - DIVYA RAJ
ROLL - 1610110123
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

void initStuff(char **argv);

unsigned int randomNum(int range);  //returns random number between 1 and range

void pickupChopsticks(int philNum);

void returnForks(int philNum);

void eat(int num);

void* philosopherWork(const int* philNumArg)
;

int N;  //Number of philosophers

pthread_mutex_t mutex;  //mutex lock used to ensure deadlock free exec
pthread_cond_t *cond;

bool *stickInUse; //True for chopstick picked up
bool *hasEaten;  //True if philosopher has eaten

int *timeEating;

int main(int argc, char* argv[])
{
	initStuff(argv);

	//starting the program clock
	time_t startTime;
	time(&startTime);

	int i;
	char cho;

	do
	{
		cho = 'n';

		pthread_mutex_init(&mutex, NULL);

		pthread_t *philosophers = malloc(N* sizeof(pthread_t));

		//start all philosophers
		for (i = 0; i < N; i++)
		{
			int *arg = malloc(sizeof(*arg));
			*arg = i;
			pthread_create(&(philosophers[i]), NULL, (void *) philosopherWork, arg);
		}

		//waiting for all philosopher threads to join
		for (i = 0; i < N; i++)
			pthread_join(philosophers[i], NULL);

		pthread_mutex_destroy(&mutex);

		printf("\nContinue? (Y/N): ");
		scanf(" %c", &cho);

	}while (cho == 'y' || cho == 'Y');


	for(i = 0; i<N; i++)
		printf("\nPhilosopher no. %d spent %d seconds eating.", i, timeEating[i]);

	//ending program clock
	time_t endTime;
	time(&endTime);
	printf("\nTotal time elapsed since starting: %.2fs \n", difftime(endTime, startTime));

	return 0;
}

void* philosopherWork(const int* philNumArg)
{
	int philNum = *philNumArg;
	printf("\nThis is philosopher number %d", philNum);

	pickupChopsticks(philNum);

	eat(philNum);

	returnForks(philNum);

	//think for awhile
	printf("\nPhilosopher number %d is thinking...", philNum);
	sleep(randomNum(3));

}

void pickupChopsticks(int philNum)
{
	pthread_mutex_lock(&mutex);

	//pickup forks
	while(stickInUse[philNum] || stickInUse[(philNum+1)%N])
	{
		printf("\nPhilosopher number %d is waiting...", philNum);
		pthread_cond_wait(&cond[philNum], &mutex);
	}

	// mark stick in use
	stickInUse[philNum] = true;
	stickInUse[(philNum+1)%N] = true;
	printf("\nPhilosopher number %d picked up stick number %d", philNum, philNum);
	printf("\nPhilosopher number %d picked up stick number %d", philNum, (philNum+1)%N);

	//eat(philNum);

	hasEaten[philNum] = true;

	pthread_mutex_unlock(&mutex);
}

void eat(int philNum)
{
	//eat for a while
	printf("\nPhilosopher number %d is eating...", philNum);
	unsigned int eatTime = randomNum(3);
	sleep(eatTime);
	timeEating[philNum] += eatTime;
}

void returnForks(int philNum)
{
	pthread_mutex_lock(&mutex);

	int left = (philNum - 1)%N;
	int right = (philNum + 1)%N;

	if(left < 0)
		left = N-1;

	// lets go of his sticks
	stickInUse[philNum] = false;
	stickInUse[(philNum+1)%N] = false;
	printf("\nPhilosopher number %d put down stick number %d", philNum, philNum);
	printf("\nPhilosopher number %d put down stick number %d", philNum, (philNum+1)%N);

	//signal others...
	/*for(int i =0; i< N; i++)
	{
		if(i != philNum && !hasEaten[i])
		{
			pthread_cond_signal(&cond[i]);
			printf("\nPhilosopher number %d signalled philosopher number %d", philNum, i);
		}
	}*/

	pthread_cond_signal(&cond[left]);
	printf("\nPhilosopher number %d signalled philosopher number %d", philNum, left);
	pthread_cond_signal(&cond[right]);
	printf("\nPhilosopher number %d signalled philosopher number %d", philNum, right);

	pthread_mutex_unlock(&mutex);
}

void initStuff(char **argv)
{
	N = atoi(argv[1]);

	timeEating = (int*) calloc(N, sizeof(int));

	srand((unsigned int) time(0));  //seeding the random no. generator with current time

	cond = malloc(N* sizeof(pthread_cond_t));
	stickInUse = malloc((N+1)* sizeof(bool));
	hasEaten = malloc((N+1)* sizeof(bool));

	for(int i=0; i<N; i++)
		hasEaten[i] = false;

	printf("Number of philosophers = %d", N);
}

unsigned int randomNum(int range)  //returns random number between 1 and range
{
	unsigned int r = (unsigned int) (1 + rand() % range);

	return r;
}
