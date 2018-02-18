/* 	Name: DIVYA RAJ
	ID: 1610110123
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

#define READ_END 0
#define WRITE_END 1

#define MAX_PATH_LENGTH 256

char *sourcePath;
char *destinationPath;

void parseArguments(int argc, char* argv[MAX_PATH_LENGTH]);

void copyFile(char *sourcePath, char *destinationPath);

void checkExceptions(char *sourcePath, char *destinationPath);

int main(int argc, char* argv[MAX_PATH_LENGTH])
{
	parseArguments(argc, argv);

	checkExceptions(sourcePath, destinationPath);

	copyFile(sourcePath, destinationPath);

	return 0;
}

void checkExceptions(char *sourcePath, char *destinationPath)
{
	char cho = 'n';

	if(access(sourcePath, F_OK) == -1)
	{
		printf("Source file doesn't exist!\n");
		exit(0);
	}

	else if(access(destinationPath, F_OK) != -1) //destination file already exists!
	{
		printf("The destination file already exists, do you want to overwrite?(y/n) ");
		scanf(" %s", &cho);

		if(cho == 'y' || cho == 'Y')
			remove(destinationPath);

		else
		{
			printf("OK!\n");
			exit(1);
		}
	}
}

void copyFile(char *sourcePath, char *destinationPath)
{
	int fd[2];   //File descriptor
	pid_t childID;

	pipe(fd); /* create pipe */

	childID = fork(); //fork child process

	if(childID == -1)
	{
		perror("fork");
		exit(1);
	}
	if(childID != 0)  //PARENT
	{
		/* parent only writes to pipe. Close the read end */
		close(READ_END);
		/* Open the source file and write to pipe */
		/* Print error message if the source file does not exist */
	}
	else  //CHILD
	{
		/* child only reads from pipe. Close the write end */
		close(fd[WRITE_END]);
		/* Open the destination file and read from pipe */
		/* Create the destination file if it does not exist */
	}
	/* Remember to close the files */

}

void parseArguments(int argc, char* argv[MAX_PATH_LENGTH])
{
	if(argc != 3)
	{
		printf("Invalid arguments!\n");
		exit(0);
	}

	else
	{
		sourcePath = strdup(argv[1]);
		destinationPath = strdup(argv[2]);
	}
}