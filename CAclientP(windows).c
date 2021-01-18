#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>

#include<error.h>
#include<string.h>
#include<unistd.h>


#include <winsock2.h>

#define MAX_CLIENTS 5
#define MAX_DATA 4096

int main(int argc, char **argv)
{
	WSADATA wsaData;
	struct sockaddr_in remote_server;
	int sock, len, cleanup;
	char input[MAX_DATA] = "Requesting Persistent Connection...\n";;
	char output[MAX_DATA];

	WSAStartup(MAKEWORD(2,2), &wsaData);
    printf("Client: Winsock DLL status is %s.\n", wsaData.szSystemStatus);


	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
        printf("Client: socket() failed! Error code: %ld\n", WSAGetLastError());
        // Do the clean up
        cleanup = WSACleanup();
        if(cleanup != 0)
        	printf("Server: WSACleanup() failed!...\n");
     	else
          	printf("Server: WSACleanup() is OK...\n");
        // Exit with error
        exit(EXIT_FAILURE);
    }
    else
        printf("Client: socket() is OK!\n"); 

	remote_server.sin_family = AF_INET;
	/* bind: socket ‘fd’ to port number*/
	remote_server.sin_port = htons(8080);
	remote_server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if((connect(sock, (struct sockaddr *)&remote_server, sizeof(struct sockaddr_in))) == -1)
	{
        printf("Client: connect() failed! Error code: %ld\n", WSAGetLastError());
        // Do the clean up
        cleanup = WSACleanup();
        if(cleanup != 0)
        	printf("Client: WSACleanup() failed!...\n");
    	else
     		printf("Client: WSACleanup() is OK...\n");
        // Exit with error
        exit(EXIT_FAILURE);
    }
    else
        printf("Client: connect() is OK!\n"); 

    len = 1;

	while(len)
	{
		//fgets(input, MAX_DATA, stdin);

		send(sock, input, strlen(input), 0);

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

    return 0;
}