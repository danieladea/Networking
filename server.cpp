#include <string>
#include <thread>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <poll.h>
#include <signal.h>
#include <sys/wait.h>
#include <netinet/in.h>

#include "CRC.h"

using namespace std;

#define BUFSIZE 1024
#define CRCSIZE 8

void checkErr(int testVal, string message)
{
//usage if testVal<0, print message with strerr and exit
  if(testVal<0)
  {
    fprintf(stderr, "Error: %s . %s \n",strerror(errno), message.c_str());
  }
}

int main(int argc, char* argv[]) 
{
	int sockfd, newsockfd, valread;
	unsigned int clilen;
	int portVal = atoi(argv[1]);
	string fileDir = argv[2];
	struct sockaddr_in serv_addr, cli_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	checkErr(sockfd, "Failed to open socket"); 

	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portVal);
	int bindTest = (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0); 
	checkErr(bindTest, "Failed to bind");

	listen(sockfd,5);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
  	checkErr(newsockfd, "Failed to accept");
  	char buffer[1024] = {0};
  	valread = read( newsockfd , buffer, 1024); 
    printf("%s\n",buffer ); 

    return 0;
}
