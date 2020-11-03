#include <string>
#include <thread>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
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
#include <arpa/inet.h>
#include <fstream>
#include <signal.h>
#include <fcntl.h>

#include "CRC.h"

using namespace std;

#define BUFSIZE 1024
#define CRCSIZE 8
#define MAX_BACKLOG 10
#define BUF_SIZE    1024        

int numFiles =0;
char* fileDir;

void checkErr(int testVal, string message)
{
//usage if testVal<0, print message with strerr and exit
  if(testVal<0)
  {
    fprintf(stderr, "ERROR: %s . %s \n",strerror(errno), message.c_str());
  }
}

void printExit(string message)
{
	fprintf(stderr, "%s\n", message.c_str());	
	exit(1);
}

void signal_callback_handler(int signum)
{
   printf("Caught signal %d\n",signum);
   exit(signum);
}

 
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck fuck
//hhhhaha i hate software engineering

/**
int DoEcho(const int clientFd, const fd_list_t *list, string fileDir)
{
    int result;
    char buffer[BUF_SIZE + 1];  // stores received message 

    (void)list;
    result = recv(clientFd, buffer, BUF_SIZE, 0);

    if (result < 0)
    {
        // receive failed 
        perror("Error receiving message from client");
    }
    else if (0 == result)
    {
        printf("Socket %d disconnected.\n", clientFd);
    }
    else
    {
        //const fd_list_t *here;

        buffer[result] = '\0';
        printf("Socket %d received %s", clientFd, buffer);
        string fileLocation = fileDir + "/" + to_string(numFiles) + ".txt";
        ofstream myfile;
        myfile.open(fileLocation);

        myfile << buffer;

      result = 1;
    }

    return result;
}
*/

void* executeThread(void* param)
{
	char path[128];
	
	sprintf(path,"%s/%d.file", fileDir, numFiles);
	int clientsockfd = *(int*)param;
	int fcntlTest = fcntl(clientsockfd, F_SETFL, O_NONBLOCK);
	if(fcntlTest)
		printExit("Failure on setting file descriptor");

	struct timeval maxTime;
	maxTime.tv_sec = 10; 
	maxTime.tv_usec = 0;

	fd_set fdList;
	FD_ZERO(&fdList);
	FD_SET(clientsockfd, &fdList);


	FILE* myfile = fopen(path, "wb");
	//ofstream myfile;
	//myfile.open(path, fstream::out);
	printf("File %s created\n", path);
	if(myfile == NULL)
		printExit("Could not create file"); 
	while(1)
	{

		int connCheck = select(clientsockfd+1, &fdList, NULL, NULL, &maxTime);
		checkErr(connCheck, "Select failed");
		if( connCheck == 0)
	 	{
		    close(clientsockfd);
		    fprintf(stderr, "ERROR: Connection timeout\n");
		    //myfile.close();
		    fclose(myfile);
		    myfile= fopen(path, "wb");
		    char errorMsg[6] = "ERROR";
		    int errWrite = fwrite(errorMsg, sizeof(char), 6, myfile);
		    checkErr(errWrite, "Could not write");

		   	//myfile << errorMsg;
		    //myfile.close();
		    fclose(myfile);
		    return 0;
		}
	
		char buffer[1024];
		memset(buffer, '\0', BUF_SIZE);
		int result = recv(clientsockfd, buffer, BUF_SIZE, 0);
		checkErr(result, "Failure on receiving data");
		if(result == 0)
		{
		    //myfile.close();
		    fclose(myfile);
	    	break;
	  	}
		else
		{
			printf("Server reads: %d\n", result);
			//myfile << buffer;
			int errWrite = fwrite(buffer, sizeof(char), result, myfile);
			checkErr(errWrite, "Could not write");
		}
		    	
	}
	return 0; 
  
}


int main(int argc, char* argv[]) 
{
  	signal(SIGTERM, signal_callback_handler);
   	signal(SIGQUIT, signal_callback_handler);
 	

	int result;
    int listenFd;   /* socket fd used to listen for connection requests */

	fileDir = argv[2];
    //struct fd_list_t *fdList, *thisFd;
    //struct pollfd *pfds;
    //int numFds, changed;

    /* structures for server and client internet addresses */
    struct sockaddr_in serverAddr;

    int i;

    /* argv[1] is port number, make sure it's passed to us */
    if (argc != 3)
    	printExit("please input a port number and file location respectively");


    /* create server socket descriptor */
    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenFd < 0)
    	printExit("Could not create socket");

    int yes = 1;
  	if (setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    	printExit("failed to use setsockopt");
    	

    memset(&serverAddr, 0, sizeof(serverAddr));     /* clear data structure */

    /* allow internet connection from any address on port argv[1] */
    serverAddr.sin_family = AF_INET;                /* internet address family */
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* any incoming address */
    serverAddr.sin_port = htons(atoi(argv[1]));     /* port number */
/*
    struct addrinfo *servinfo;
    int addressTest = getaddrinfo(NULL, htons(atoi(argv[1])), &serverAddr, &servinfo);
    if (addressTest != 0)
    	printExit("could not resolve address");
*/
    /* bind to the local address */
    result = bind(listenFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    if (result < 0)
    {
        /* bind failed */
        close(listenFd);
        printExit("Failed to bind");
    }

    /* listen for incoming connections */
    result = listen(listenFd, MAX_BACKLOG);

    if (result < 0)
    {
        /* listen failed */
        perror("Error listening for connections");
        exit(1);
    }


    while(1)
    {

		struct sockaddr_in clientAddr;
		socklen_t clientAddrSize = sizeof(clientAddr);
		int clientSockfd = accept(listenFd, (struct sockaddr*)&clientAddr, &clientAddrSize);
		checkErr(clientSockfd, "failed to accept");

			
		//char ipstr[INET_ADDRSTRLEN] = {'\0'};
		//inet_ntop(clientAddr.sin_family, &clientAddr.sin_addr, ipstr, sizeof(ipstr));
		//ntohs(clientAddr.sin_port) << std::endl;
		char ipstr[INET_ADDRSTRLEN] = {'\0'};
  		inet_ntop(clientAddr.sin_family, &clientAddr.sin_addr, ipstr, sizeof(ipstr));
  		std::cout << "Accept a connection from: " << ipstr << ":" << ntohs(clientAddr.sin_port) << std::endl;
		
		numFiles++;
		pthread_t thread_id;
		if(pthread_create(&thread_id, NULL, executeThread, (void*)&clientSockfd))
			printExit("pthread error");

		pthread_detach(thread_id);	
    }
    return 0;
}
