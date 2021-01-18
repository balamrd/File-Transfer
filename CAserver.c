#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<error.h>
#include<strings.h>
#include<unistd.h>
#include<arpa/inet.h>

#define MAX_CLIENTS 5
#define MAX_DATA 4096
#define LENGTH 512

void str_ser(int sockfd);   

int main(int argc, char **argv)
{
	int sockfd, con_fd, ret;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size;

//	char *buf;
	pid_t pid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);          //create socket
	if (sockfd <0)
	{
		printf("error in socket!");
		exit(1);
	}
	
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(8080);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr("127.0.0.1");
	bzero(&(my_addr.sin_zero), 8);
	ret = bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr));                //bind socket
	if (ret <0)
	{
		printf("error in binding");
		exit(1);
	}
	
	ret = listen(sockfd, BACKLOG);                              //listen
	if (ret <0) {
		printf("error in listening");
		exit(1);
	}

	while (1)
	{
		printf("Server listening...\n");
		sin_size = sizeof (struct sockaddr_in);
		con_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);            //accept the packet
		if (con_fd <0)
		{
			printf("error in accept\n");
			exit(1);
		}

		if ((pid = fork())==0)                                         // creat acception process
		{
			close(sockfd);
			str_ser(con_fd);                                          //receive packet and response
			close(con_fd);
			exit(0);
		}
		else close(con_fd);                                         //parent process
	}
	close(sockfd);
	printf("Client disconnected \n");
	exit(0);
}

void str_ser(int sockfd)

	char buf[BUFSIZE];
	FILE *fp;
	char recvs[DATALEN];
	int end, n = 0, n1 = 0;
	long lseek=0;
	end = 0;

	while(!end) {
	len = recv(conn, input, MAX_DATA, 0);
	if (input == "Requesting Persistent connection..." || "Requesting Non-persistent connection...") {
		send(sock, input, strlen(input), 0);
		input[len] = '\0';
		printf("%s\n", input);
	}
	else 
		printf("Hello World!!!!\n");

	}
	return;