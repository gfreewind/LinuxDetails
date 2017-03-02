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
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>

#define SERVER_PATH	"./unix_server"
#define CLIENT_PATH	"./unix_client"

#define BIND_UNIX_CLIENT

static void* client_thread(void *data)
{
	int fd = socket(AF_UNIX, SOCK_DGRAM, 0);

#ifdef BIND_UNIX_CLIENT
	struct sockaddr_un cli_addr;
	memset(&cli_addr, 0, sizeof(cli_addr));
	cli_addr.sun_family = AF_UNIX;
	strcpy(cli_addr.sun_path, CLIENT_PATH);
	unlink(CLIENT_PATH);
	if (bind(fd, (struct sockaddr*)&cli_addr, sizeof(cli_addr))) {
		printf("Fail to bind client\n");
		exit(1);
	}
#endif

	struct sockaddr_un serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, SERVER_PATH);

	sendto(fd, "123", 3, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	close(fd);

	return NULL;

}

int main(void)
{
	pthread_t tid;

	signal(SIGPIPE, SIG_IGN);

	int server_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	struct sockaddr_un serv_addr; 
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, SERVER_PATH);
	unlink(SERVER_PATH);
	if (bind(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
		printf("Fail to bind\n");
		exit(-1);
	}
	
	pthread_create(&tid, NULL, client_thread, NULL);

	char buf[32] = {0};
	struct sockaddr_un peer_addr;
	socklen_t sock_len;

	memset(&peer_addr, 0, sizeof(peer_addr));
	sock_len = sizeof(peer_addr);
	recvfrom(server_fd, buf, sizeof(buf), 0, (struct sockaddr*)&peer_addr, &sock_len);

	printf("buf: %s\n", buf);
	printf("peer sun_path: %s\n", peer_addr.sun_path);
	
	close(server_fd);
	pthread_join(tid, NULL);

	return 0;
}
