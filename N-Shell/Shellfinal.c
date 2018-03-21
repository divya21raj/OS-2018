#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <pwd.h>

#define max 80

void  parse(char *line, char **args);
void  execute(char **args,int stat);
void add_history(char *temp);
char* exec_history(char *str);
void view_history();

char historyPath[256];

int main(void)
{
	struct passwd *pw = getpwuid(getuid());  /*getting the user's home directory*/
	char *homedir = pw->pw_dir;

	strcpy(historyPath, homedir);
	strcat(historyPath, "/history.txt"); //initialising path to history

	int shouldrun = 1;					/* flag to determine when to exit program */
	char  *line;							//input line
 	char  *args[max/2 +1];						//array of pointers to character

	while (shouldrun)
  	{
		printf("osh>");
    	fflush(stdout);

		line = malloc(max);

		scanf("%[^\t\n]s",line);

		printf("%s\n",line);
		printf("%c\n",line[0]);
		printf("%d",strcmp(line,"!!"));

		if(strcmp(line,"!!")==0)
		{
			printf("checking conditions");
			char *his = malloc(max);char *temp=malloc(max);
			FILE *fi = fopen(historyPath,"r");
			while(fgets(temp,(max/2),fi)!=NULL)
				his = temp;
			fclose(fi);
			add_history(his);
			line = his;
		}

		if(line[0] == '!',line[1] != '!')
		{
			FILE *fi = fopen(historyPath,"r");
			char *his;char *temp=malloc(max);
			int i = atoi(line +1);
			printf("%d",i);
			for(;i>0;--i)
			{
				if(fgets(temp,(max/2),fi)==NULL)
				{
					his = "No event found\n";
					fclose(fi);

				}
			}
			his = temp;
			fclose(fi);
			add_history(his);
			line = his;
		}

		parse(line,args);			// parsing the line removing whitespaces

		if(strcmp(args[0], historyPath)==0)
    	      		view_history();

	    	if(line[strlen(line)-2]=='&')
    	  		execute(args,0);

    		else
    	    		execute(args,1);

    		add_history(line);

	}
  	return 0;
}

// PARSING THE STRINGS INTO TOKENS.

void  parse(char *inp, char **args)
{
		printf("This is the Parse Function");
		char *p;
		int i = 0;
		p = strtok(inp, " ");
		while(i<(max/2 + 1))
		{
			args[i] = p;
			puts(args[i]);
			puts(p);
			p = strtok(NULL, " ");
			if(p == NULL)
				break;
			i++;
		}
		args[++i] = NULL;                                                                // mark the end of argument list
}

// FORKING FUNCTION.

void  execute(char **args,int stat)
{
     pid_t  pid;
     pid = fork();                                                                            // forking a child process
     if (pid  < 0)
     {
          printf("Child process could not be forked\n");
          exit(1);
     }
     else if (pid == 0)
     {
          if (execvp(*args, args) < 0) {                                                      //executing command
               printf("Execution failed\n");
               exit(1);
          }
     }
     else
     {
          if(stat)
               while (wait(&stat) != pid) ;                                                        // wait function for completeion

     }
}


// TO ADD HISTORY.

void add_history(char *temp)
{
	FILE *fi = fopen(historyPath,"a");
	char *command = temp;
	strcat(command,"\n");
	if(fi!=NULL)
	{
		fprintf(fi,"%s",command);
		fclose(fi);
	}
}

/*char* exec_history(char *str)
{

	printf("this is exec_history function");
	char *his,*temp=NULL;
	FILE *fi = fopen(historyPath,"r");
	if(fi!=NULL && strlen(str)>0)
	{
		if(str[1] == '!')
		{
			while(fgets(temp,(max/2),fi)!=NULL)
				his = temp;
			fclose(fi);
			add_history(his);
			return his;
		}
		else
		{
			int i = atoi(str+1);
			for(;i>0;--i)
			{
				if(fgets(temp,(max/2),fi)==NULL)
				{
					his = "No event found\n";
					fclose(fi);
					return his;
				}
			}
			his = temp;
			fclose(fi);
			add_history(his);
			return his;
		}
	}
	else
		his = "No history found\n";
	fclose(fi);
	return his;
}
*/
void view_history()
{
	FILE *fi = fopen(historyPath,"r");
	char str[max]; int i=1;
	if(fi!=NULL)
	{
		while(fgets(str,max,fi)!=NULL)
		{
			printf("%d  %s",i,str);
			++i;
		}
	}
	else
		printf("No history found\n");
	fclose(fi);
}