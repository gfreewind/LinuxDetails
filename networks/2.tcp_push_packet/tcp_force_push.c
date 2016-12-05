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
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>


#define ENABLE_NODELAY_TEST
typedef int bool;

#define true 1
#define false 0

#define PACKET_CNT		5

static volatile bool g_server_listen = false;

static void* client_thread(void *data)
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	int i;
	int opt;

	// wait parent listen
	while (!g_server_listen) {
		sleep(1);
	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = 0x010007f;
	serv_addr.sin_port = htons(6000);

	connect(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
#ifdef ENABLE_NODELAY_TEST
	/* Enable TCP_NODELAY, it could force PUSH  */
	opt = 1;
	setsockopt(fd, SOL_TCP, TCP_NODELAY, &opt, sizeof(opt));
#else
	/* Disable TCP_CORK, it dosn't make sure force PUSH */
	opt = 0;
	setsockopt(fd, SOL_TCP, TCP_CORK, &opt, sizeof(opt));
#endif

	for (i = 0; i < PACKET_CNT; ++i) {
		send(fd, "1", 1, 0);
#ifndef ENABLE_NODELAY_TEST
		opt = 0;
		setsockopt(fd, SOL_TCP, TCP_CORK, &opt, sizeof(opt));
#endif
	}
	close(fd);

	return NULL;

}

int main(void)
{
	pthread_t tid;
	int ret;
	int i;

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

	char buf[32];
	for (i = 0; i < PACKET_CNT; ++i) {
		memset(buf, 0, sizeof(buf));
		ret = read(client, buf, 32);
		printf("server: recive %d bytes: %s\n", ret, buf);
	}

	close(client);
	printf("server: close fd at the first time\n");

err2:
	close(listen_fd);
err1:
	pthread_join(tid, NULL);

	return 0;
}
