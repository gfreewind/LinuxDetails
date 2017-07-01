/*
 * =====================================================================================
 *
 *       Filename:  tcp_keepalive_reporter
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/18/2017 10:04:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
/* According to POSIX.1-2001 */
#include <sys/select.h>
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/epoll.h>


#define PEER_ADDR		(0x7F000001)
#define PEER_PORT		(34567)

//#define USE_SELECT
#define USE_EPOLL

int main(void)
{
	struct sockaddr_in peer;
	int ret;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	int optval;
	int err;
	char buf[512];
	socklen_t len = sizeof(err);

	memset(&peer, 0, sizeof(peer));

	peer.sin_family = AF_INET;
	peer.sin_port = htons(PEER_PORT);
	peer.sin_addr.s_addr = htonl(PEER_ADDR);


	ret = connect(sock, (const struct sockaddr *)&peer, sizeof(peer));

	if (ret) {
		printf("Fail to connect myself: %s\n", strerror(errno));
		exit(1);
	}
	printf("Connect successfully\n");

	optval = 1;
	ret = setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));
	if (ret) {
		printf("Fail to set SO_KEEPALIVE\n");
		exit(1);
	}

	optval = 5;
	ret = setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE, &optval, sizeof(optval));
	if (ret) {
		printf("Fail to set TCP_KEEPIDLE: %s\n", strerror(errno));
		exit(1);
	}
	optval = 2;
	ret = setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL, &optval, sizeof(optval));
	if (ret) {
		printf("Fail to set TCP_KEEPINTVL: %s\n", strerror(errno));
		exit(1);
	}
	optval = 3;
	ret = setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT, &optval, sizeof(optval));
	if (ret) {
		printf("Fail to set TCP_KEEPCNT: %s\n", strerror(errno));
		exit(1);
	}

	
#ifdef USE_SELECT
	fd_set rfds;

	FD_ZERO(&rfds);

	FD_SET(sock, &rfds);

	ret = select(sock+1, &rfds, NULL, NULL, NULL);
	if (ret) {
		printf("select returns %d\n", ret);
		if (FD_ISSET(sock, &rfds)) {
			printf("Receive RD event by select\n");
		}
	}
#endif

#ifdef USE_EPOLL
	int ep = epoll_create(1024);
	if (ep == -1) {
		printf("Fail to epoll_create: %s\n", strerror(errno));
		exit(1);
	}

	struct epoll_event evt;

	memset(&evt, 0, sizeof(evt));
	evt.events |= EPOLLIN;
	evt.data.fd = sock;

	ret = epoll_ctl(ep, EPOLL_CTL_ADD, sock, &evt);
	if (ret) {
		printf("Fail to epoll_ctl: %s\n", strerror(errno));
		exit(1);
	}

	memset(&evt, 0, sizeof(evt));
	ret = epoll_wait(ep, &evt, 1, -1);
	if (ret) {
		if (evt.events & EPOLLIN) {
			printf("Receive RD event by epoll\n");
		}
	}
	
	close(ep);
#endif

	err = 0;
	ret = getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &len); 
	if (ret) {
		printf("Fail to getsockopt\n");
		exit(1);
	}
	printf("sock err is %d\n", err);

	ret = read(sock, buf, 512);
	printf("Read %d bytes\n", ret);

	close(sock);
	return 0;
}

