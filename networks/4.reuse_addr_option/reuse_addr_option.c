#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define LOCAL_PORT	(12345)

static void test_udp_any_addr_same_port_diff_ifs(void)
{
        int udp_fd1 = socket(AF_INET, SOCK_DGRAM, 0);
        int udp_fd2 = socket(AF_INET, SOCK_DGRAM, 0);

        struct sockaddr_in addr_in;
        memset(&addr_in, 0, sizeof(addr_in));
        addr_in.sin_family = AF_INET;
        addr_in.sin_port = htons(LOCAL_PORT);
        addr_in.sin_addr.s_addr = INADDR_ANY;

	char *opt = "eth0";
	if (setsockopt(udp_fd1, SOL_SOCKET, SO_BINDTODEVICE, opt, strlen(opt))) {
		printf("UDP1 fail to bind eth0. %s:%d\n", strerror(errno), errno);
	}
	opt = "eth1";
	if (setsockopt(udp_fd2, SOL_SOCKET, SO_BINDTODEVICE, opt, strlen(opt))) {
		printf("UDP2 fail to bind eth1. %s:%d\n", strerror(errno), errno);
	}

        if (bind(udp_fd1, (const struct sockaddr *)&addr_in, sizeof(addr_in)) != 0) {
                printf("UDP1 fail to bind any addr and port(%d) on eth0\n", LOCAL_PORT);
        }

        if (bind(udp_fd2, (const struct sockaddr *)&addr_in, sizeof(addr_in)) != 0) {
                printf("UDP2 fail to bind any addr and port(%d) on eth1 \n", LOCAL_PORT);
        }

        close(udp_fd1);
        close(udp_fd2);

        printf("UDP could bind two any addrs with same port and diff ifs without SO_REUSEADDR\n");
}


static void test_udp_diff_addr_same_port(struct in_addr *addr)
{
        int udp_fd1 = socket(AF_INET, SOCK_DGRAM, 0);
        int udp_fd2 = socket(AF_INET, SOCK_DGRAM, 0);

        struct sockaddr_in addr_in;
        memset(&addr_in, 0, sizeof(addr_in));
        addr_in.sin_family = AF_INET;
        addr_in.sin_port = htons(LOCAL_PORT);
        addr_in.sin_addr = *addr;

        if (bind(udp_fd1, (const struct sockaddr *)&addr_in, sizeof(addr_in)) != 0) {
                printf("UDP1 fail to bind local addr and  port(%d)\n", LOCAL_PORT);
        }

	addr_in.sin_addr.s_addr = 0x0100007f;
        if (bind(udp_fd2, (const struct sockaddr *)&addr_in, sizeof(addr_in)) != 0) {
                printf("UDP2 fail to bind any addr and port(%d)\n", LOCAL_PORT);
        }

        close(udp_fd1);
        close(udp_fd2);

	printf("UDP could bind two different addr with same port without SO_REUSEADDR\n");
}

static void test_udp_any_addr_same_port(void)
{
        int udp_fd1 = socket(AF_INET, SOCK_DGRAM, 0);
        int udp_fd2 = socket(AF_INET, SOCK_DGRAM, 0);

        struct sockaddr_in addr_in;
        memset(&addr_in, 0, sizeof(addr_in));
        addr_in.sin_family = AF_INET;
        addr_in.sin_port = htons(LOCAL_PORT);
        addr_in.sin_addr.s_addr = INADDR_ANY;

        int enable = 1;
        setsockopt(udp_fd1, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
        setsockopt(udp_fd2, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

        if (bind(udp_fd1, (const struct sockaddr *)&addr_in, sizeof(addr_in)) != 0) {
                printf("UDP1 fail to bind any addr and  port(%d)\n", LOCAL_PORT);
        }

        if (bind(udp_fd2, (const struct sockaddr *)&addr_in, sizeof(addr_in)) != 0) {
                printf("UDP2 fail to bind any addr and port(%d)\n", LOCAL_PORT);
        }

        close(udp_fd1);
        close(udp_fd2);

	printf("UDP could bind two any addrs with same port with SO_REUSEADDR\n");
}

static void test_udp_any_and_local_addr_same_port(struct in_addr *addr)
{
        int udp_fd1 = socket(AF_INET, SOCK_DGRAM, 0);
        int udp_fd2 = socket(AF_INET, SOCK_DGRAM, 0);

        struct sockaddr_in addr_in;
        memset(&addr_in, 0, sizeof(addr_in));
        addr_in.sin_family = AF_INET;
        addr_in.sin_port = htons(LOCAL_PORT);
        addr_in.sin_addr.s_addr = INADDR_ANY;

        int enable = 1;
        setsockopt(udp_fd1, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
        setsockopt(udp_fd2, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

        if (bind(udp_fd1, (const struct sockaddr *)&addr_in, sizeof(addr_in)) != 0) {
                printf("UDP1 fail to bind any addr and  port(%d)\n", LOCAL_PORT);
        }

        addr_in.sin_addr= *addr;

        if (bind(udp_fd2, (const struct sockaddr *)&addr_in, sizeof(addr_in)) != 0) {
                printf("UDP2 fail to bind local addr and port(%d)\n", LOCAL_PORT);
        }

        close(udp_fd1);
        close(udp_fd2);

	printf("UDP could bind any addr and one local addr with same port with SO_REUSEADDR\n");
}

static void test_udp_local_and_any_addr_same_port(struct in_addr *addr)
{
        int udp_fd1 = socket(AF_INET, SOCK_DGRAM, 0);
        int udp_fd2 = socket(AF_INET, SOCK_DGRAM, 0);

        struct sockaddr_in addr_in;
        memset(&addr_in, 0, sizeof(addr_in));
        addr_in.sin_family = AF_INET;
        addr_in.sin_port = htons(LOCAL_PORT);
        addr_in.sin_addr = *addr;

        int enable = 1;
        setsockopt(udp_fd1, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
        setsockopt(udp_fd2, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

        if (bind(udp_fd1, (const struct sockaddr *)&addr_in, sizeof(addr_in)) != 0) {
                printf("UDP1 fail to bind local addr and  port(%d)\n", LOCAL_PORT);
        }

	addr_in.sin_addr.s_addr = INADDR_ANY;

        if (bind(udp_fd2, (const struct sockaddr *)&addr_in, sizeof(addr_in)) != 0) {
                printf("UDP2 fail to bind any addr and port(%d)\n", LOCAL_PORT);
        }

        close(udp_fd1);
        close(udp_fd2);
	printf("UDP could bind one local addr and one any addr with same port with SO_REUSEADDR\n");
}

static void test_udp_local_addr_same_port(struct in_addr *addr)
{
	int udp_fd1 = socket(AF_INET, SOCK_DGRAM, 0);
	int udp_fd2 = socket(AF_INET, SOCK_DGRAM, 0);
	
	struct sockaddr_in addr_in;
        memset(&addr_in, 0, sizeof(addr_in));
        addr_in.sin_family = AF_INET;
        addr_in.sin_port = htons(LOCAL_PORT);
        addr_in.sin_addr = *addr;

	int enable = 1;
	setsockopt(udp_fd1, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
	setsockopt(udp_fd2, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

        if (bind(udp_fd1, (const struct sockaddr *)&addr_in, sizeof(addr_in)) != 0) {
                printf("UDP1 fail to bind port(%d)\n", LOCAL_PORT);
        }

        if (bind(udp_fd2, (const struct sockaddr *)&addr_in, sizeof(addr_in)) != 0) {
                printf("UDP2 fail to bind port(%d)\n", LOCAL_PORT);
        }
	
	close(udp_fd1);
	close(udp_fd2);

	printf("UDP could bind two local addrs and port with SO_REUSEADDR\n");
}

static void test_tcp_udp_same_port(struct in_addr *addr)
{
	int tcp_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (tcp_fd == -1) {
		printf("Fail to create tcp fd\n");
		exit(1);
	}
	int udp_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (udp_fd == -1) {
		printf("Fail to creat udp fd\n");
		exit(1);
	}
	
	struct sockaddr_in addr_in;
	memset(&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(LOCAL_PORT);
	addr_in.sin_addr = *addr;

	if (bind(tcp_fd, (const struct sockaddr *)&addr_in, sizeof(addr_in)) != 0) {
		printf("TCP fail to bind port(%d)\n", LOCAL_PORT);
	}

	if (bind(udp_fd, (const struct sockaddr *)&addr_in, sizeof(addr_in)) != 0) {
		printf("UDP fail to bind port(%d)\n", LOCAL_PORT);
	}

	close(tcp_fd);
	close(udp_fd);

	printf("TCP and UDP could bind same port seperately\n");
}

int main(int argc, const char **argv)
{
	struct in_addr addr;

	if (argc < 2) {
		printf("Please specify local IP address\n");
		return 1;
	}

	memset(&addr, 0, sizeof(addr));
	if (inet_pton(AF_INET, argv[1], &addr) != 1) {
		printf("Invalid IP address");
		return 1;
	}


	test_tcp_udp_same_port(&addr);
	test_udp_local_addr_same_port(&addr);
	test_udp_local_and_any_addr_same_port(&addr);
	test_udp_any_and_local_addr_same_port(&addr);
	test_udp_any_addr_same_port();
	test_udp_diff_addr_same_port(&addr);	
	test_udp_any_addr_same_port_diff_ifs();
	
	return 0;
}


