#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<error.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define MAX_CLIENTS 5
#define MAX_DATA 4096

void main(int argc, char **argv)
{
	int sockfd, ret, check = 0;
	float ti, rt;
	long len;
	struct sockaddr_in ser_addr;
	char ** pptr;
	struct hostent *sh;
	struct in_addr **addrs;
	FILE *fp;
	char input[50];
	/*
	printf("Enter the ip address: ");
   	fgets(str, 20, stdin);
   	strtok(str, "\n");
   	sh = gethostbyname(str);
*/
	argv[1] = "127.0.0.1";
	sh = gethostbyname(argv[1]);	                                       //get host's information
	if (sh == NULL) {
		printf("error when gethostby name");
		exit(0);
	}

	printf("canonical name: %s\n", sh->h_name);					//print the remote host's information
	for (pptr=sh->h_aliases; *pptr != NULL; pptr++)
		printf("the aliases name is: %s\n", *pptr);
	switch(sh->h_addrtype)
	{
		case AF_INET:
			printf("AF_INET\n");
		break;
		default:
			printf("unknown addrtype\n");
		break;
	}
        
	addrs = (struct in_addr **)sh->h_addr_list;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);                           //create the socket
	if (sockfd <0)
	{
		printf("error in socket");
		exit(1);
	}
	ser_addr.sin_family = AF_INET;                                                      
	ser_addr.sin_port = htons(8080);
	memcpy(&(ser_addr.sin_addr.s_addr), *addrs, sizeof(struct in_addr));
	bzero(&(ser_addr.sin_zero), 8);
	ret = connect(sockfd, (struct sockaddr *)&ser_addr, sizeof(struct sockaddr));         //connect the socket with the host
	if (ret != 0) {
		printf ("connection failed\n"); 
		close(sockfd); 
		exit(1);
	}

	while(len)
	{

		strcpy(input, "Requesting Non-persistent connection...");
		send(sock, *input, strlen(*input), 0);

		len = recv(sock, output, MAX_DATA, 0);
		printf("Data length: %d\n", len);
		if (len > 1) {
			output[len] = '\0';
			printf("%s \n", output);
		}
		else if (len == 1) {
			if (*output == '\n')  {
				len = 0;
			}
			output[len] = '\0';
			printf("%s \n", output);
		}
		else {
			len = 0;
		}


	}

	close(sock);

    return;
}
