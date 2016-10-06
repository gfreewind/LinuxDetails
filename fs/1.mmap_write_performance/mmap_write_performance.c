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

#define TEST_LOOPS	(1000000)

int main(void)
{
	int cost, i, fd;
	time_t start, end;
	char buf[5120] = {"Hello world!\n"};

	start = time(NULL);
	fd = open("./mmap_write.txt", O_CREAT|O_RDWR|O_TRUNC, 0644);
	ftruncate(fd, 1024);
	for (i = 0; i < TEST_LOOPS; ++i) {
		char *addr = mmap(NULL, 1024, PROT_WRITE, MAP_SHARED, fd, 0);
		memcpy(addr, buf, 1024);
		munmap(addr, 1024);
	}
	close(fd);
	end = time(NULL);
	cost = end - start;
	printf("mmap write 1024 bytes %u times costs %d secs\n", TEST_LOOPS, cost);

	start = time(NULL);
	fd = open("./mmap_write.txt", O_CREAT|O_RDWR|O_TRUNC);
	ftruncate(fd, 2048);
	for (i = 0; i < TEST_LOOPS; ++i) {
		char *addr = mmap(NULL, 2048, PROT_WRITE, MAP_SHARED, fd, 0);
		memcpy(addr, buf, 2048);
		munmap(addr, 2048);
	}
	close(fd);
	end = time(NULL);
	cost = end - start;
	printf("mmap write 2048 bytes %u times costs %d secs\n", TEST_LOOPS, cost);

	start = time(NULL);
	fd = open("./mmap_write.txt", O_CREAT|O_RDWR|O_TRUNC);
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
	fd = open("./mmap_write.txt", O_CREAT|O_RDWR|O_TRUNC);
	ftruncate(fd, 5120);
	for (i = 0; i < TEST_LOOPS; ++i) {
		char *addr = mmap(NULL, 5120, PROT_WRITE, MAP_SHARED, fd, 0);
		memcpy(addr, buf, 5120);
		munmap(addr, 5120);
	}
	close(fd);
	end = time(NULL);
	cost = end - start;
	printf("mmap write 5120 bytes %u times costs %d secs\n", TEST_LOOPS, cost);


        start = time(NULL);
	fd = open("./direct_write.txt", O_CREAT|O_RDWR|O_TRUNC, 0644);
        for (i = 0; i < TEST_LOOPS; ++i) {
		pwrite(fd, buf, 1024, 0);
        }
	close(fd);
        end = time(NULL);
        cost = end - start;
        printf("direct write 1024 bytes %u times costs %d secs\n", TEST_LOOPS, cost);

        start = time(NULL);
	fd = open("./direct_write.txt", O_CREAT|O_RDWR|O_TRUNC, 0644);
        for (i = 0; i < TEST_LOOPS; ++i) {
		pwrite(fd, buf, 2048, 0);
        }
	close(fd);
        end = time(NULL);
        cost = end - start;
        printf("direct write 2048 bytes %u times costs %d secs\n", TEST_LOOPS, cost);

        start = time(NULL);
	fd = open("./direct_write.txt", O_CREAT|O_RDWR|O_TRUNC, 0644);
        for (i = 0; i < TEST_LOOPS; ++i) {
		pwrite(fd, buf, 4096, 0);
        }
	close(fd);
        end = time(NULL);
        cost = end - start;
        printf("direct write 4096 bytes %u times costs %d secs\n", TEST_LOOPS, cost);

        start = time(NULL);
	fd = open("./direct_write.txt", O_CREAT|O_RDWR|O_TRUNC, 0644);
        for (i = 0; i < TEST_LOOPS; ++i) {
		pwrite(fd, buf, 5120, 0);
        }
	close(fd);
        end = time(NULL);
        cost = end - start;
        printf("direct write 5120 bytes %u times costs %d secs\n", TEST_LOOPS, cost);



	return 0;
}

