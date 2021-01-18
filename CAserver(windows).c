#include<stdio.h>
#include<stdlib.h>

#include <winsock2.h>
#include<error.h>
#include<strings.h>
#include<unistd.h>
#include <dirent.h>



#define MAX_CLIENTS 5
#define MAX_DATA 4096
#define LENGTH 512


void main(int argc, char *argv[])
{
	WSADATA wsaData;
	struct sockaddr_in server;
	struct sockaddr_in client;
	int sock, conn, cleanup, len;
	int sockaddr_len = sizeof(struct sockaddr_in);
	char input[MAX_DATA];
	char *cwd[MAX_DATA];
	char *output[MAX_DATA];
	DIR *folder;
    struct dirent *entry;
    int files = 0;



	// Start of Server Initialisation
	WSAStartup(MAKEWORD(2,2), &wsaData);
    printf("Server: Winsock DLL status is %s.\n", wsaData.szSystemStatus);

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
        printf("Server: socket() failed! Error code: %ld\n", WSAGetLastError());
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
        printf("Server: socket() is OK!\n"); 

	server.sin_family = AF_INET;
	/* bind: socket ‘fd’ to port number*/
//	server.sin_port = htons(atoi(argv[1]));
	server.sin_port = htons(8080);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if((bind(sock, (struct sockaddr *)&server, sockaddr_len)) == -1)
	{
        printf("Server: bind() failed! Error code: %ld\n", WSAGetLastError());
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
        printf("Server: bind()) is OK!\n"); 

	if((listen(sock, MAX_CLIENTS)) == -1)
	{
        printf("Server: listen() failed! Error code: %ld\n", WSAGetLastError());
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
        printf("Server: listen() is OK!\n"); 

    // End of Server Initialisation


	while(1)
	{
		printf("Server listening...\n");


		if((conn = accept(sock, (struct sockaddr *)&client, &sockaddr_len)) == -1)
		{
        	printf("Server: accept() failed! Error code: %ld\n", WSAGetLastError());
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
        	printf("Server: accept() is OK!\n"); 

		printf("New client connected from port number %d and IP address %s \n", ntohs(client.sin_port), inet_ntoa(client.sin_addr));

		len = recv(conn, input, MAX_DATA, 0);
		if (input == "Requesting Persistent connection..." || "Requesting Non-persistent connection...") {
			send(sock, input, strlen(input), 0);
			input[len] = '\0';
			printf("%s\n", input);
		}
		else 
			printf("Hello World!!!!\n");

		
		folder = opendir("./Data/");
    	if(folder == NULL)
    	{
        	printf("Unable to read directory\n");
        	exit(EXIT_FAILURE);
    	}
    	*cwd = strtok(folder->dd_name, "*");
    	printf("Current Work Directory = %s\n", *cwd);
    	closedir(folder);


    	folder = opendir("./Data/");
    	if(folder == NULL)
    	{
        	printf("Unable to read directory\n");
        	exit(EXIT_FAILURE);
    	}
    	while((entry=readdir(folder)))
    	{
    		//printf("%s\n", entry->d_name);
    		if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
    			files++;
        		printf("File %d: %s\n", files, entry->d_name);
        	}
    	}
    	closedir(folder);
		
		//strcat(*cwd, entry->d_name);

		//FILE *fs = fopen(cwd, "r");

		/*
		if(!GetCurrentDirectory(MAX_DATA, cwd)) {
			printf("GetCurrentDirectory() failed!\n");
		}
		printf("Your current directory is: %s\n", cwd);
		strcat(cwd, "\\Data\\");
		printf("Your new current directory is: %s\n", cwd);
		*filenames = GetFileName(cwd);
		puts(*filenames);
		*/
/*
		len = 1;

		while(len)
		{
			
			len = recv(conn, data, MAX_DATA, 0);

			printf("Data length: %d\n", len);

			if (len > 1) {
				send(conn, data, len, 0);
				data[len] = '\0';
				printf("Sent message: %s\n", data);
			}
			else if (len == 1) {
				if (*data == '\n')  {
					len = 0;
				}
			}
			else {
				len = 0;
			}
			
		}
*/
		printf("Client disconnected \n");

		close(conn);
		return;
	}

}


