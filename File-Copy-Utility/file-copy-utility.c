/* 	Name: DIVYA RAJ
	ID: 1610110123
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <wait.h>

#define READ_END 0
#define WRITE_END 1

#define MAX_PATH_LENGTH 256
#define MAX_FILE_SIZE 2048 //2GB!

char *sourcePath;
char *destinationPath;

void parseArguments(int argc, char* argv[MAX_PATH_LENGTH]);

void copyFile(char *sourcePath, char *destinationPath);

void checkExceptions(char *sourcePath, char *destinationPath);

void appendSourceFileName(char *destinationPath, char *sourcePath);

int main(int argc, char* argv[MAX_PATH_LENGTH])
{
	parseArguments(argc, argv);

	checkExceptions(sourcePath, destinationPath);

	copyFile(sourcePath, destinationPath);

	return 0;
}

void copyFile(char *sourcePath, char *destinationPath)
{
	int fd[2];   //File descriptor
	pid_t childID;

	FILE *source, *destination;

	char *sourceString, *destString;
	long fileSize;

	pipe(fd); /* create pipe */

	childID = fork(); //fork child process

	if(childID == -1)
	{
		printf("FORK ERROR!\n");
		exit(1);
	}

	else if(childID == 0)  //CHILD
	{
		close(fd[READ_END]);   /* child only writes to pipe. Close the read end */

		source = fopen(sourcePath, "r");   /* Open the source file*/

		fseek(source, 0L, SEEK_END);    /*Getting the*/
		fileSize = ftell(source);		/*file size. */
		fseek(source, 0L, SEEK_SET);

		sourceString = malloc(fileSize);

		fread (sourceString, 1, fileSize, source);

		write(fd[WRITE_END], sourceString, strlen(sourceString)+1);

		close(fd[WRITE_END]);
		fclose(source);
	}

	else  //PARENT
	{
		wait(NULL);

		close(fd[WRITE_END]); /* parent only reads from pipe. Close the write end */

		destination = fopen(destinationPath, "w");
		destString = malloc(fileSize);

		/* read from the pipe */
		do
		{
			read(fd[READ_END], destString, MAX_FILE_SIZE);
		}
		while(destString == NULL);

		fprintf(destination, "%s", destString);

		close(fd[READ_END]);
		fclose(destination);
	}
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

		appendSourceFileName(destinationPath, sourcePath);
	}
}

void appendSourceFileName(char *destinationPath, char *sourcePath)
{
	char *sourceFileName = malloc(MAX_PATH_LENGTH/4);

	int i, j=0;

	for(i=0; i<strlen(sourcePath); i++)
	{
		if(sourcePath[i] == '/')
		{
			memset(sourceFileName,0,strlen(sourceFileName));
			j=0;
		}
		else
			sourceFileName[j++] = sourcePath[i];
	}

	if(destinationPath[strlen(destinationPath) - 1] == '/')
		strcat(destinationPath, sourceFileName);
	else
	{
		memmove(sourceFileName + 1, sourceFileName, strlen(sourceFileName));
		sourceFileName[0] = '/';

		strcat(destinationPath, sourceFileName);
	}
}