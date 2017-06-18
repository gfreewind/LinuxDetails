/*
 * =====================================================================================
 *
 *       Filename:  no_listen_tcp_conn.c
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

#define LOCAL_IP_ADDR		(0x7F000001)
#define LOCAL_TCP_PORT		(34567)

int main(void)
{
	struct sockaddr_in local, peer;
	int ret;
	char buf[128];
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	memset(&local, 0, sizeof(local));
	memset(&peer, 0, sizeof(peer));

	local.sin_family = AF_INET;
	local.sin_port = htons(LOCAL_TCP_PORT);
	local.sin_addr.s_addr = htonl(LOCAL_IP_ADDR);

	peer = local;	

	ret = bind(sock, (const struct sockaddr *)&local, sizeof(local));
	ret = connect(sock, (const struct sockaddr *)&peer, sizeof(peer));

	if (ret) {
		printf("Fail to connect myself: %s\n", strerror(errno));
		exit(1);
	}
	printf("Connect to myself successfully\n");

	strcpy(buf, "Hello, myself~");
	send(sock, buf, strlen(buf), 0);

	memset(buf, 0, sizeof(buf));
	recv(sock, buf, sizeof(buf), 0);

	printf("Recv the msg: %s\n", buf);
	close(sock);
	return 0;
}

