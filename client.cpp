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
#include <netdb.h>
#include <string>
#include <thread>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include <iostream>
#include <sstream>

//#include "CRC.h"

using namespace std;

#define BUFSIZE 1024
#define CRCSIZE 8

void printExit(char *eString, char *eMessage)
{
  fprintf(stderr, "Error: %s. %s \n",eString,  eMessage);
  exit(1);
}

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

int result;
    int socketFd;               /* TCP/IP socket descriptor */

    /* structures for use with getaddrinfo() */
    struct addrinfo hints;      /* hints for getaddrinfo() */
    struct addrinfo *servInfo;  /* list of info returned by getaddrinfo() */
    struct addrinfo *p;         /* pointer for iterating list in servInfo */

    /* argv[1] is host name, argv[2] is port number, make sure we have them */
    if (argc != 3)
    {
        fprintf(stderr,
            "Usage:  %s <server hostname or address> <port number>\n",
            argv[0]);
        exit(1);
    }

    memset(&hints, 0, sizeof(hints));

    /* type of server we're looking for */
    hints.ai_family = AF_INET;          /* internet address family */
    hints.ai_socktype = SOCK_STREAM;    /* stream sock */
    hints.ai_protocol = IPPROTO_TCP;    /* tcp/ip protocol */
    hints.ai_flags = AI_CANONNAME;      /* include canonical name */

    /* get a linked list of likely servers pointed to by servInfo */
    result = getaddrinfo(argv[1], argv[2], &hints, &servInfo);



    p=servInfo;

    while (p != NULL)
    {
        /* use current info to create a socket */
        socketFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

        if (socketFd >= 0)
        {
            /***************************************************************
 *             * We got the socket we asked for try to connect.
 *                         *
 *                                     * NOTE: connect() has an unspecified time out.  For a good
 *                                                 * a sample of connecting with a timeout see
 *                                                             * http://developerweb.net/viewtopic.php?id=3196 for
 *                                                                         ***************************************************************/
            result = connect(socketFd, p->ai_addr, p->ai_addrlen);

            if (result != 0)
            {
                /* this socket wouldn't except our connection */
                close(socketFd);
            }
            else
            {
                /* we're connected, get out of this loop */
                break;
            }
        }

        p = p->ai_next;     /* try next address */
    }

    if (NULL == p)
    {
        /* we never found a server to connect to */
        fprintf(stderr, "Unable to connect to server.\n");
        freeaddrinfo(servInfo);
        exit(EXIT_FAILURE);
    }

	/*string hostname = argv[1]; 
	int portVal = atoi(argv[2]);
	string filename = argv[3];
	  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);     // short, network byte order
  serverAddr.sin_addr.s_addr = inet_addr(hostname);
  memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));
\
if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
    perror("connect");
    return 2;
  }

  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  if (getsockname(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen) == -1) {
    perror("getsockname");
    return 3;
  }

  char ipstr[INET_ADDRSTRLEN] = {'\0'};
  inet_ntop(clientAddr.sin_family, &clientAddr.sin_addr, ipstr, sizeof(ipstr));
  std::cout << "Set up a connection from: " << ipstr << ":" <<
    ntohs(clientAddr.sin_port) << std::endl;
/*	
	cout << "yeet";
//
	struct sockaddr_in serv_addr;
  	struct hostent *server; 
  	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  	checkErr(sockfd, "Failed to create socket");

 	memset((char *) &serv_addr, 0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portVal);
	cout << "tweet";
	memcpy( (char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr,server->h_length);

	int connectTest = connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
	checkErr(connectTest, "Failed to connect socket");
//
*/
	char buffer[4] = "fuc";
	//ifstream myFile("filename");


	checkedWrite(socketFd, buffer,4);



	

	close(socketFd);


    return 0;
}



