#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;

	/* create new process by calling fork() */
	pid = fork();
	
	if (pid < 0) {
	/* error */
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if (pid == 0 ) {
	/* child process */
	execlp("/bin/ls", "ls", NULL);
	}
	else {
	/* parent process */
	wait (NULL);
	printf("Child Complete! \n");
	}
	
	return 0;
}


