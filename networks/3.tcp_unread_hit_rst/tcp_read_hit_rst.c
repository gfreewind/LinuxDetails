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
#include <errno.h>

typedef int bool;

#define true 1
#define false 0

#define PACKET_CNT		5

static volatile bool g_server_listen = false;
static volatile bool g_client_send = false;
static volatile bool g_server_close = false;

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
	/* Enable TCP_NODELAY, it could force PUSH  */
	opt = 1;
	setsockopt(fd, SOL_TCP, TCP_NODELAY, &opt, sizeof(opt));

	for (i = 0; i < PACKET_CNT; ++i) {
		send(fd, "1", 1, 0);
	}
	g_client_send = true;
	
	while (!g_server_close) {
		sleep(1);
	}
	
	char buf[32];
	int ret = read(fd, buf, sizeof(buf));
	
	printf("ret: %d. error: %s(%d)\n", ret, strerror(errno), errno);

	close(fd);

	return NULL;

}

int main(void)
{
	pthread_t tid;

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

	if (!g_client_send) {
		sleep(1);
	}

	close(client);
	printf("server: close fd\n");
	g_server_close = true;

err2:
	close(listen_fd);
err1:
	pthread_join(tid, NULL);

	return 0;
}
