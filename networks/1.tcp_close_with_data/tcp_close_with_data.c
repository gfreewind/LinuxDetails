/*
 * =====================================================================================
 *
 *       Filename:  tcp_close_with_data.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/31/2016 09:29:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gao Feng gfree.wind@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>

typedef int bool;

#define true 1
#define false 0

static volatile bool g_server_listen = false;

static void* client_thread(void *data)
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	int ret;

	// wait parent listen
	while (!g_server_listen) {
		sleep(1);
	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = 0x010007f;
	serv_addr.sin_port = htons(6000);

	// Fist time
	connect(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	send(fd, "First", sizeof("First"), 0);

	// parent close already
	char buf[2048];
	ret = read(fd, buf, 32);
	printf("client: ret is %d\n", ret);
	close(fd);

	fd = socket(AF_INET, SOCK_STREAM, 0);
	ret = connect(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (ret) {
		printf("connect failed: %s\n", strerror(errno));
		return 0;
	}
	send(fd, buf, 2048, 0);

	// parent close already
	ret = read(fd, buf, 32);
	printf("client: ret is %d: %s\n", ret, strerror(errno));
	close(fd);

	return NULL;

}

int main(void)
{
	pthread_t tid;
	int ret;

	signal(SIGPIPE, SIG_IGN);

	pthread_create(&tid, NULL, client_thread, NULL);

	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd == -1) {
		printf("socket failed\n");
		goto err1;
	}

	int opt = 1;
	setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in serv_addr; 
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(6000);

	if (bind(listen_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
		printf("bind failed\n");
		goto err2;
	}
	
	if (listen(listen_fd, 5)) {
		printf("listen failed\n");
		goto err2;
	}
	g_server_listen = true;

	int client = accept(listen_fd, NULL, 0);
	if (client == -1) {
		printf("accept failed\n");
		goto err2;
	}

	/*
	First time:
	Server close the fd after receive all data
	*/	
	char buf[32] = {0};
	ret = read(client, buf, 32);
	printf("server: receive %d bytes: %s\n", ret, buf);
	
	close(client);
	printf("server: close fd at the first time\n");

	client = accept(listen_fd, NULL, 0);

	/*
	Second time:
	Server close the fd without reading data
	*/
	close(client);
	printf("server: close fd at the second time\n");

err2:
	close(listen_fd);
err1:
	pthread_join(tid, NULL);

	return 0;
}
