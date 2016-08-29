#include <stdlib.h>
#include <stdio.h>


#include <unistd.h>
#include <wait.h>

int main(void)
{
	pid_t child;

	printf("Hello, ");

	child = fork();
	if (child == -1) {
		printf("fork failed\n");
		exit(1);
	} else if (child == 0) {
		// Child
		printf("I'm child\n");
		exit(0);
	}

	// Parent
	printf("I'm parent\n");

	waitpid(child, NULL, 0);

	return 0;
}
