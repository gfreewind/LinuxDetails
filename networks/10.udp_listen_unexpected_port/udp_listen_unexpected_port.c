#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <linux/in.h>

int main(void)
{
        int sock;

        if((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
     	   exit(1);
        }

	int flags = fcntl(sock, F_GETFL, 0);
	fcntl(sock, F_SETFL, flags | O_NONBLOCK | O_CLOEXEC);

	struct sockaddr_in serv_addr;

        bzero(&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
        serv_addr.sin_port = htons(50505);

        char msg[4];
        sendto(sock, (char*)&msg, sizeof(msg), 0, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));

        return 0;

}
