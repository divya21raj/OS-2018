/* 	Name: DIVYA RAJ
	ID: 1610110123
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

#define READ_END 0
#define WRITE_END 1

#define MAX_PATH_LENGTH 128

char *sourcePath;
char *destinationPath;

void parseArguments(int argc, char* argv[MAX_PATH_LENGTH]);

int main(int argc, char* argv[MAX_PATH_LENGTH])
{
	int fd[2];   //File descriptor
	pid_t childID;

	int i;
	for(i=0; i<argc; i++)
		printf("%s\n", argv[i]);

	parseArguments(argc, argv);

	pipe(fd); /* create pipe */
	if((childID = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	if(childID == 0)
	{
	/* child only reads. Close the write end */
		close(fd[WRITE_END]);
	/* Open the destination file and read from pipe */
	/* Create the destination file if it does not exist */
	}
	else
	{
	/* parent only writes. Close the read end */
		close(READ_END);
	/* Open the source file and write to pipe */
	/* Print error message if the source file does not exist */
	}
	/* Remember to close the files */

	return 0;
}

void parseArguments(int argc, char* argv[MAX_PATH_LENGTH])
{
	if(argc > 3)
	{
		printf("Invalid arguments!\n");
		exit(0);
	}

	else if(argc == 1)
	{
		printf("No arguments!\n");
		exit(0);
	}

	else
	{
		sourcePath = strdup(argv[1]);
		destinationPath = strdup(argv[2]);
	}
}