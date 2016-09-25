/*
 * =====================================================================================
 *
 *       Filename:  mkfifo_with_nonblock.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/25/2016 09:33:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gao Feng, gfree.wind@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define TEST_PIPE_FILE	"./test.pipe"

int main(void)
{
	remove(TEST_PIPE_FILE);
	if (mkfifo(TEST_PIPE_FILE, 0644)) {
		printf("mkfifo failed, %s(%d)\n", strerror(errno), errno);
		return -1;
	}

	int fd = open(TEST_PIPE_FILE, O_WRONLY|O_NONBLOCK);
	if (fd == -1) {
		printf("open with O_WRONLY|O_NONBLOCK failed, %s(%d)\n",
			strerror(errno), errno);
	} else {
		printf("open with O_WRONLY|O_NONBLOCK is successful, return fd(%d)\n", fd);
		close(fd);
	}
	
	fd = open(TEST_PIPE_FILE, O_RDONLY|O_NONBLOCK);
	if (fd == -1) {
		printf("open with O_RDONLY|O_NONBLOCK failed, %s(%d)\n",
			strerror(errno), errno);
	} else {
		printf("open with O_RDONLY|O_NONBLOCK is successful, return fd(%d)\n", fd);
		close(fd);
	}

	return 0;
}
