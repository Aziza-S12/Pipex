#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

// int main(void)
// {
// 	pid_t	pid;

// 	printf("Fork here\n");
// 	pid = fork();
// 	if ( pid == -1) //error
// 		return (1);
// 	printf("\nFork successful\n");
// 	if (pid == 0)
// 		printf("I'm the child, my internal pid is %d\n", pid);
// 	else if (pid > 0)
// 		printf("I'm the parent, my child's pid is %d\n", pid);
// 	return (0);

// }

int main(void)
{
	pid_t	pid;
	int		ends[2]; //the 2 ends of the pipe: ends[0]: read end; ends[1]: write end
	char	secret[30];
	int		reader;
	char	buffer[30];

	if (pipe(ends) == -1) //create a pipe and error check
		return(1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{ //child process
		close(ends[0]); //nothing we wanna read, close pipe's read end
		printf("Child: I'm writing my secret in the pipe..\n");
		strcpy(secret, "I won smth");
		write(ends[1], secret, strlen(secret));
		close(ends[1]);
		return(0);
	}
	else //parent process
	{
		close(ends[1]); //nothing to write, close pipe's write end
		waitpid(pid, NULL, 0); //Wait for child
		printf("Parent: I received my child. What is its secret?\n");
		reader = read(ends[0], buffer, 30);
		close(ends[0]); //Read everything, close pipe's read end
		if (reader == -1)
			return(3);
		buffer[reader] = '\0';
		printf("Parent: The secret is..%s\n", buffer);
	}
}