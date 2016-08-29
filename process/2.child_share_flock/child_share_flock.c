/*
 * =====================================================================================
 *
 *       Filename:  child_inherit_flock.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/26/2016 10:01:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int fd = open("./test_flock.txt", O_RDWR|O_CREAT, 0644);
	if (fd == -1) {
		printf("Fail to open file\n");
		exit(1);
	}

	int ret = flock(fd, LOCK_EX);
	if (ret == -1) {
		printf("Fail to flock\n");
		exit(1);
	}
	printf("Parent get the flock at the first time\n");

	pid_t child = fork();
	if (child == -1) {
		printf("Fail to fork\n");
		exit(1);
	} else if (child == 0) {
		printf("Child sleeps now\n");
		sleep(30);
		printf("Child wakes up and exits\n");
		exit(1);
	}

	flock(fd, LOCK_UN);
	printf("Parent release the lock\n");
	printf("Parent tries to get flock again\n");
	flock(fd, LOCK_EX);
	printf("Parent gets the lock at the second time\n");

	waitpid(child, NULL, 0);

	printf("Parent exit\n");

	return 0;
}

