#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//#define USE_CLIB

#define TEST_FILE	"./tmp.txt"

#define LOOPS		(1000000)


#ifdef USE_CLIB
struct thr_data {
	FILE *fp;
	const char *data;
};

static void * write_data(void *data)
{
	struct thr_data *d;
	size_t len;
	int i;

	d = data;
	len = strlen(d->data);
	for (i = 0; i < LOOPS; ++i) {
		fwrite(d->data, len, 1, d->fp);
	}

	return NULL;
}

#else
struct thr_data {
	int fd;
	const char *data;
};

static void *write_data(void *data)
{
	struct thr_data *d;
	int i;
	size_t len;

	d = data;
	len = strlen(d->data);
	for (i = 0; i < LOOPS; ++i) {
		write(d->fd, d->data, len); 
	}

	return NULL;
}
#endif



int main(void)
{
	pthread_t t1, t2, t3;
	struct thr_data d1, d2, d3;

#ifdef USE_CLIB
	FILE *fp = fopen(TEST_FILE, "w");
	d1.fp = d2.fp = d3.fp = fp;
#else
	//int fd = open(TEST_FILE, O_WRONLY|O_TRUNC);
	int fd = open(TEST_FILE, O_WRONLY|O_TRUNC|O_APPEND);
	d1.fd = d2.fd = d3.fd = fd;
#endif

	d1.data = "aaaaaa\n";
	d2.data = "bbbbbb\n";
	d3.data = "cccccc\n";

	pthread_create(&t1, NULL, write_data, &d1);
	pthread_create(&t2, NULL, write_data, &d2);
	pthread_create(&t3, NULL, write_data, &d3);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

#ifdef USE_CLIB
	fclose(fp);
#else
	close(fd);
#endif

	return 0;
}
