#include <string>
#include <thread>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>


#include <iostream>
#include <sstream>

#include "CRC.h"

using namespace std;

#define BUFSIZE 1024
#define CRCSIZE 8

void checkErr(int testVal, char* message)
{
//usage if testVal<0, print message with strerr and exit
  if(testVal<0)
  {
    fprintf(stderr, "Error: %s . %s \n",strerror(errno), message);
  }
}

void checkedWrite(int sockfd, char *buffer, int size)
{
	int cWrite;
	cWrite = write(sockfd, buffer, size);
	if(cWrite<0)
    	printExit(strerror(errno), "Failed to write");
}

int main(int argc, char* argv[]) 
{

	
	string hostname = argv[1]; 
	int portVal = argv[2];
	string filename = argv[3];
//
	struct sockaddr_in serv_addr;
  	struct hostent *server; 
  	sockfd = socket(AF_INET, SOCK_STREAM, 0);
  	checkErr(sockfd, "Failed to create socket");

 	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portVal);

	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

	int connectTest = connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
	checkErr(connectTest, "Failed to connect socket");
//
	char buffer[4] = "test";
	//ifstream myFile("filename");


	checkedWrite(sockfd, &buffer,4)



	

	close(sockfd);


    return 0;
}



