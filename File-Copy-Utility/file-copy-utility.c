/* 	Name: DIVYA RAJ
	ID: 1610110123
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <wait.h>
#include <stdbool.h>
#include <sys/stat.h>

#define READ_END 0
#define WRITE_END 1

#define MAX_PATH_LENGTH 256
#define BUFFER_SIZE 128

char *sourcePathGlobal;
char *destinationPathGlobal;

void parseArguments(int argc, char* argv[MAX_PATH_LENGTH]);

void copyFile(char *sourcePath, char *destinationPath);

void checkExceptions(char *sourcePath, char *destinationPath);

void appendSourceFileName(char *destinationPath, char *sourcePath);

bool isFolder(char *path);

void handleAlreadyExisting();

bool rootExists(char *path);

bool hasSlash(char *path);



int main(int argc, char* argv[MAX_PATH_LENGTH])
{
	parseArguments(argc, argv);  //parse out sourcePathGlobal and destinationPathGlobal

	checkExceptions(sourcePathGlobal, destinationPathGlobal); //checking exceptions like files not existing, overwrite

	copyFile(sourcePathGlobal, destinationPathGlobal);

	return 0;
}

void copyFile(char *sourcePath, char *destinationPath)
{
	int fd[2];   //File descriptor
	pid_t childID;

	FILE *source, *destination;

	char *sourceString = malloc(BUFFER_SIZE), *destString = malloc(BUFFER_SIZE);   //strings that will hold the contents to be copied

	pipe(fd); /* create pipe */

	source = fopen(sourcePath, "r");   /* Open the source file*/
	destination = fopen(destinationPath, "w"); /*Open the destination file*/

	childID = fork(); //fork child process

		if (childID == -1)
		{
			printf("FORK ERROR!\n");
			exit(1);
		}

		else if (childID == 0)  //CHILD
		{
			close(fd[READ_END]);   /* child only writes to pipe. Close the read end */

			while(fgets(sourceString, sizeof(sourceString), source))
			{

				if(write(fd[WRITE_END], sourceString, strlen(sourceString)) < 1)
				{
					printf("\nPipe Error!\n");
					exit(1);
				}
			}

			close(fd[WRITE_END]);
		}

		else  //PARENT
		{
			wait(NULL);

			close(fd[WRITE_END]); /* parent only reads from pipe. Close the write end */

			/* read from the pipe */
			while (read(fd[READ_END], destString, BUFFER_SIZE))
			{
				fprintf(destination, "%s", destString);

				memset(destString, 0, sizeof(destString));
			}

			close(fd[READ_END]);
		}

	fclose(source);
	fclose(destination);
}

void checkExceptions(char *sourcePath, char *destinationPath)
{

	if(access(sourcePath, F_OK) == -1)
	{
		printf("Source file doesn't exist!\n");
		exit(0);
	}

	if(!hasSlash(destinationPath))  //no '/' in the input, i.e should be in the current directory
	{
		char currentPath[1024];
		getcwd(currentPath, sizeof(currentPath));  //get current path

		char *temp = strdup(destinationPath);
		memset(destinationPath, 0, sizeof(destinationPath));
		destinationPath = strdup(currentPath);

		strcat(destinationPath, "/");
		strcat(destinationPath, temp);  //current path added before file name

		destinationPathGlobal = destinationPath;
	}

	if(isFolder(destinationPath))  //destination provided is an existing folder
	{
		appendSourceFileName(destinationPath, sourcePath);  //appending file name to given folder directory
		if(access(destinationPath, F_OK) == 0)
			handleAlreadyExisting();
	}

	else if(access(destinationPath, F_OK) == 0) //destination is a file and already exists
		handleAlreadyExisting();

	else if(rootExists(destinationPath))
	{
		//Is a file but doesn't exist and needs to be created ... proceed
	}

	else
	{
		printf("Failed to access %s.... invalid directory!\n", destinationPath);
		exit(1);
	}
}

bool hasSlash(char *path)
{
	int i;
	bool flag = false;

	for(i = 0; i< strlen(path); i++)
	{
		if(strcmp(path + i, "\\") < 0)
		{
			flag = true;
			break;
		}
	}

	return flag;
}

bool rootExists(char *path)
{
	int i;
	bool flag = false;

	char *temp = strdup(path);

	for(i = (int) (strlen(path) - 1); i >= 0; i--)
	{
		if(strcmp(path + i, "\\") < 0)
		{
			temp[i + 1] = 0;
			break;
		}
	}

	if(access(temp, F_OK) == 0)
		flag = true;

	return flag;
}

void handleAlreadyExisting()
{
	char *overWrite = malloc(sizeof(char));

	fflush(stdin);
	printf("The destination file already exists, do you want to overwrite?(y/n) ");
	fgets(overWrite, sizeof(overWrite), stdin);

	if(*overWrite == 'n' || *overWrite == 'N')
	{
		exit(1);
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
		sourcePathGlobal = strdup(argv[1]);
		destinationPathGlobal = strdup(argv[2]);
	}
}

bool isFolder(char *path)
{
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISDIR(path_stat.st_mode);
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