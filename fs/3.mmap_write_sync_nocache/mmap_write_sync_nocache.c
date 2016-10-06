/*
 * =====================================================================================
 *
 *       Filename:  mmap_write_performance.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/06/2016 12:20:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gao Feng (gfree.wind@gmail.com)
 *        Company:  
 *
 * =====================================================================================
 */

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define TEST_LOOPS	(10000000)

int main(void)
{
	int cost, i, fd;
	time_t start, end;
	char buf[20480] = {"Hello world!\n"};

	start = time(NULL);
	fd = open("./mmap_write.txt", O_CREAT|O_RDWR|O_TRUNC|O_DIRECT|O_SYNC, 0644);
	ftruncate(fd, 4096);
	for (i = 0; i < TEST_LOOPS; ++i) {
		char *addr = mmap(NULL, 4096, PROT_WRITE, MAP_SHARED, fd, 0);
		memcpy(addr, buf, 4096);
		munmap(addr, 4096);
	}
	close(fd);
	end = time(NULL);
	cost = end - start;
	printf("mmap write 4096 bytes %u times costs %d secs\n", TEST_LOOPS, cost);

	start = time(NULL);
	fd = open("./mmap_write.txt", O_CREAT|O_RDWR|O_TRUNC|O_DIRECT|O_SYNC);
	ftruncate(fd, 8192);
	for (i = 0; i < TEST_LOOPS; ++i) {
		char *addr = mmap(NULL, 8192, PROT_WRITE, MAP_SHARED, fd, 0);
		memcpy(addr, buf, 8192);
		munmap(addr, 8192);
	}
	close(fd);
	end = time(NULL);
	cost = end - start;
	printf("mmap write 8192 bytes %u times costs %d secs\n", TEST_LOOPS, cost);

	start = time(NULL);
	fd = open("./mmap_write.txt", O_CREAT|O_RDWR|O_TRUNC|O_DIRECT|O_SYNC);
	ftruncate(fd, 12288);
	for (i = 0; i < TEST_LOOPS; ++i) {
		char *addr = mmap(NULL, 12288, PROT_WRITE, MAP_SHARED, fd, 0);
		memcpy(addr, buf, 12288);
		munmap(addr, 12288);
	}
	close(fd);
	end = time(NULL);
	cost = end - start;
	printf("mmap write 12288 bytes %u times costs %d secs\n", TEST_LOOPS, cost);
	

        start = time(NULL);
	fd = open("./direct_write.txt", O_CREAT|O_RDWR|O_TRUNC|O_DIRECT|O_SYNC, 0644);
        for (i = 0; i < TEST_LOOPS; ++i) {
		pwrite(fd, buf, 4096, 0);
        }
	close(fd);
        end = time(NULL);
        cost = end - start;
        printf("direct write 4096 bytes %u times costs %d secs\n", TEST_LOOPS, cost);

        start = time(NULL);
	fd = open("./direct_write.txt", O_CREAT|O_RDWR|O_TRUNC|O_DIRECT|O_SYNC, 0644);
        for (i = 0; i < TEST_LOOPS; ++i) {
		pwrite(fd, buf, 8192, 0);
        }
	close(fd);
        end = time(NULL);
        cost = end - start;
        printf("direct write 8192 bytes %u times costs %d secs\n", TEST_LOOPS, cost);

        start = time(NULL);
	fd = open("./direct_write.txt", O_CREAT|O_RDWR|O_TRUNC|O_DIRECT|O_SYNC, 0644);
        for (i = 0; i < TEST_LOOPS; ++i) {
		pwrite(fd, buf, 12288, 0);
        }
	close(fd);
        end = time(NULL);
        cost = end - start;
        printf("direct write 12288 bytes %u times costs %d secs\n", TEST_LOOPS, cost);


	return 0;
}

