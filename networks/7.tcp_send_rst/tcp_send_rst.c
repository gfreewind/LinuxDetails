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
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>


#define PEER_ADDR		(0x7F000001)
#define PEER_PORT		(34567)

int main(void)
{
	struct sockaddr_in peer;
	struct linger linger;
	int ret;
	int sock = socket(AF_INET, SOCK_STREAM, 0);

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

	memset(&linger, 0, sizeof(linger));
	linger.l_onoff = 1;
	linger.l_linger = 0;

	ret = setsockopt(sock, SOL_SOCKET, SO_LINGER, &linger, sizeof(linger));
	if (ret) {
		printf("Fail to set linger\n");
		exit(1);
	}

	close(sock);

	printf("Done\n");
	return 0;
}

