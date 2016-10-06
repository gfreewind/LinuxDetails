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

#define TEST_LOOPS	(5000000)

int main(void)
{
	int cost, i, fd;
	time_t start, end;
	char buf[20480];

	start = time(NULL);
	fd = open("./mmap_read.txt", O_CREAT|O_RDWR|O_TRUNC|O_DIRECT|O_SYNC, 0644);
	ftruncate(fd, 4096);
	for (i = 0; i < TEST_LOOPS; ++i) {
		char *addr = mmap(NULL, 4096, PROT_READ, MAP_SHARED, fd, 0);
		memcpy(buf, addr, 4096);
		munmap(addr, 4096);
	}
	close(fd);
	end = time(NULL);
	cost = end - start;
	printf("mmap read 4096 bytes %u times costs %d secs\n", TEST_LOOPS, cost);

	start = time(NULL);
	fd = open("./mmap_read.txt", O_CREAT|O_RDWR|O_TRUNC|O_DIRECT|O_SYNC);
	ftruncate(fd, 8196);
	for (i = 0; i < TEST_LOOPS; ++i) {
		char *addr = mmap(NULL, 8196, PROT_READ, MAP_SHARED, fd, 0);
		memcpy(buf, addr, 8196);
		munmap(addr, 8196);
	}
	close(fd);
	end = time(NULL);
	cost = end - start;
	printf("mmap read 8196 bytes %u times costs %d secs\n", TEST_LOOPS, cost);

	start = time(NULL);
	fd = open("./mmap_read.txt", O_CREAT|O_RDWR|O_TRUNC|O_DIRECT|O_SYNC);
	ftruncate(fd, 12288);
	for (i = 0; i < TEST_LOOPS; ++i) {
		char *addr = mmap(NULL, 12288, PROT_READ, MAP_SHARED, fd, 0);
		memcpy(buf, addr, 12288);
		munmap(addr, 12288);
	}
	close(fd);
	end = time(NULL);
	cost = end - start;
	printf("mmap read 12288 bytes %u times costs %d secs\n", TEST_LOOPS, cost);
	

        start = time(NULL);
	fd = open("./direct_read.txt", O_CREAT|O_RDWR|O_TRUNC|O_DIRECT|O_SYNC, 0644);
	ftruncate(fd, 4096);
        for (i = 0; i < TEST_LOOPS; ++i) {
		pread(fd, buf, 4096, 0);
        }
	close(fd);
        end = time(NULL);
        cost = end - start;
        printf("direct read 4096 bytes %u times costs %d secs\n", TEST_LOOPS, cost);

        start = time(NULL);
	fd = open("./direct_read.txt", O_CREAT|O_RDWR|O_TRUNC|O_DIRECT|O_SYNC, 0644);
	ftruncate(fd, 8192);
        for (i = 0; i < TEST_LOOPS; ++i) {
		pread(fd, buf, 8192, 0);
        }
	close(fd);
        end = time(NULL);
        cost = end - start;
        printf("direct read 8192 bytes %u times costs %d secs\n", TEST_LOOPS, cost);

        start = time(NULL);
	fd = open("./direct_read.txt", O_CREAT|O_RDWR|O_TRUNC|O_DIRECT|O_SYNC, 0644);
	ftruncate(fd, 12288);
        for (i = 0; i < TEST_LOOPS; ++i) {
		pread(fd, buf, 12288, 0);
        }
	close(fd);
        end = time(NULL);
        cost = end - start;
        printf("direct read 12288 bytes %u times costs %d secs\n", TEST_LOOPS, cost);


	return 0;
}

