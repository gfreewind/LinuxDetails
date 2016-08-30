#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(void)
{
	int fd1 = open("./test1.txt", O_WRONLY|O_CREAT, 0644);
	if (fd1 == -1) {
		printf("Fail to open ./test1.txt\n");
		exit(1);
	}

	pid_t child = fork();
	if (child == -1) {
		printf("Fail to fork\n");
		exit(1);
	} else if (child == 0) {
		// Child
		int fd2 = open("./test2.txt", O_WRONLY|O_CREAT, 0644);
		if (fd2 == -1) {
			printf("Child fails to open ./test2.txt\n");
			exit(1);
		}

		write(fd1, "I'm child\n", sizeof("I'm child\n"));
		write(fd2, "I'm child\n", sizeof("I'm child\n"));

		close(fd1);
		close(fd2);

		exit(0);
	}

	// Parent
	int fd2 = open("./test2.txt", O_WRONLY|O_CREAT, 0644);
	if (fd2 == -1) {
		printf("Parent fails to open ./test2.txt\n");
		waitpid(child, NULL, 0);
		exit(1);
	}

	write(fd1, "I'm parent\n", sizeof("I'm parent\n"));
	write(fd2, "I'm parent\n", sizeof("I'm parent\n"));
	
	close(fd1);
	close(fd2);


	waitpid(child, NULL, 0);

	return 0;
}
