/* 	Name: DIVYA RAJ
	IDs: 1610110123
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int fd[2];
	pid_t cpID;

	pipe(fd); /* create pipe */
	if((cpID = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	if(cpID == 0)
	{
	/* child only reads. Close the write end */
		close(fd[1]);
	/* Open the destination file and read from pipe */
	/* Create the destination file if it does not exist */
	}
	else
	{
	/* parent only writes. Close the read end */
		close(...);
	/* Open the source file and write to pipe */
	/* Print error message if the source file does not exist */
	}
	/* Remember to close the files */

	return 0;
}