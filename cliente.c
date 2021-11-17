#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<winsock2.h>
#include <windows.h>

void main() {
	
	char cadena[1024];
	int sockfd;
	struct sockaddr_in servaddr;
	
	char sendLine[1024] = "Usando el Puerto 22000\n";
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr, 0, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(22000);
	
	inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));
	connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	
	printf("\n\n\t\t--------Se inicio el chat--------\n\n");
	
	while(!strstr(cadena, "adios") && !strstr(sendLine, "adios")) {
		
		memset(&cadena, 0, 1024);
		
		gets(sendLine);
		write(sockfd, sendLine, strlen(sendLine) + 1);
		
		if (!strstr(sendLine, "adios")) {
			read(sockfd, cadena, 1024);
			printf("%s", cadena);
		}
		
	}
	
	printf("\n\n Conversacion Finalizada... \n");
	
}
