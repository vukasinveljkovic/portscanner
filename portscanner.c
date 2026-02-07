#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	short int open_ports = 0;

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sock < 0)
	{
		perror("SOCKET FAIL: ");
		return -1;
	}
	
	struct sockaddr_in remote;

	memset(&remote, 0, sizeof(remote));
	
	remote.sin_family = AF_INET;
	
	if(inet_aton(argv[1], &remote.sin_addr) < 1)
	{
		perror("ADDRESS FAIL: ");
		return -1;
	}
	
	for(int i = 1; i < 1024; i++)
	{
		remote.sin_port = htons(i);
		int connection = connect(sock, (struct sockaddr *) &remote, sizeof(remote));
		if(connection >= 0)
		{	
			open_ports += 1;
			printf("PORT %d OPEN\n", i);
		}
		close(sock);
		sock = socket(AF_INET, SOCK_STREAM, 0);
	}
	
	printf("TCP Scan Complete:\n");
	
	if(open_ports)
	{
		if(open_ports > 1)
		{
			printf("%d ports are open\n", open_ports);
		}
		else
		{
			printf("%d port is open\n", open_ports);
		}
	}
	else
	{
		printf("None of the scanned ports are open\n");
		printf("Maybe just use Nmap :P\n");
	}

	return 0;
}
