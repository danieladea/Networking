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
#include <fstream>


#include "CRC.h"

using namespace std;

#define BUFSIZE 1024
#define CRCSIZE 8
#define MAX_BACKLOG 10
#define BUF_SIZE    1024        

int numFiles =1;
void checkErr(int testVal, string message)
{
//usage if testVal<0, print message with strerr and exit
  if(testVal<0)
  {
    fprintf(stderr, "Error: %s . %s \n",strerror(errno), message.c_str());
  }
}

typedef struct fd_list_t
{
    int fd;
    struct fd_list_t* next;
} fd_list_t;

int DoEcho(const int clientFd, const fd_list_t *list, string fileDir)
{
    int result;
    char buffer[BUF_SIZE + 1];  /* stores received message */

    (void)list;
    result = recv(clientFd, buffer, BUF_SIZE, 0);

    if (result < 0)
    {
        /* receive failed */
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
        /*******************************************************************
 *         * echo the buffer to all connected sockets, skip if waiting
 *                 * is required.  Use threads or a complex polling loop if it's
 *                         * important that every socket receive the echo.
 *                                 *******************************************************************/
      result = 1;
    }

    return result;
}


/***************************************************************************
 * *   Function   : InsertFd
 * *   Description: This routine will traverse a linked list of file
 * *                descriptors.  If it reaches the end of the list without
 * *                finding the file descriptor passed a as parameter, it
 * *                will insert a node for the new file descriptor at the end
 * *                of the list.
 * *   Parameters : fd - The socket descriptor to be inserted to the list.
 * *                list - a pointer to a list of fds for all connected
 * *                sockets.
 * *   Effects    : A node for the fd is added to the end of the list of fds.
 * *   Returned   : 0 for success, otherwise errno for the failure.
 * *
 * *   NOTE: If duplicates aren't an issue, it's faster to insert the new
 * *         file descriptor to the head of the linked list.
 * ***************************************************************************/
int InsertFd(int fd, fd_list_t **list)
{
    fd_list_t *here;

    /* handle empty list */
    if (NULL == *list)
    {
        *list = (fd_list_t *)malloc(sizeof(fd_list_t));

        if (NULL == list)
        {
            perror("Error allocating fd_list_t");
            return errno;
        }

        (*list)->fd = fd;
        (*list)->next = NULL;
        return 0;
    }

    /* find the end of the list */
    here = *list;
    while(here->next != NULL)
    {
        if (here->fd == fd)
        {
            fprintf(stderr, "Tried to insert fd that already exists: %d\n", fd);
            return EEXIST;  /* is there a better errno? */
        }

        here = here->next;
    }

    /* we're at the end make sure that fd isn't already here */
    if (here->fd == fd)
    {
        fprintf(stderr, "Tried to insert fd that already exists: %d\n", fd);
        return EEXIST;  /* is there a better errno? */
    }

    /* add new fd to list */
    here->next = (fd_list_t *)malloc(sizeof(fd_list_t));

    if (NULL == here->next)
    {
        perror("Error allocating fd_list_t");
        return errno;
    }

    here->next->fd = fd;
    here->next->next = NULL;
    return 0;
}


/***************************************************************************
 * *   Function   : RemoveFd
 * *   Description: This routine will traverse a linked list of file
 * *                descriptors until it finds a node for the file descriptor
 * *                passed a as parameter.  Then it will remove that node from
 * *                the list.  If the file descriptor is not found, ENOENT
 * *                is returned.
 * *   Parameters : fd - The socket descriptor to be deleted from the list.
 * *                list - a pointer to a list of fds for all connected
 * *                sockets.
 * *   Effects    : The node for the fd is removed from the list of fds.
 * *   Returned   : 0 for success, otherwise ENOENT for the failure.
 * ***************************************************************************/
int RemoveFd(int fd, fd_list_t **list)
{
    fd_list_t *here, *prev;

    if (NULL == *list)
    {
        return 0;
    }

    here = *list;
    prev = NULL;

    while (here != NULL)
    {
        if (here->fd == fd)
        {
            /* found it */
            if (NULL == prev)
            {
                /* deleted the head */
                *list = here->next;
            }
            else
            {
                prev->next = here->next;
            }

            free(here);
            return 0;
        }

        prev = here;
        here = here->next;
    }

    return ENOENT;
}


/***************************************************************************
 * *   Function   : PrintFdList
 * *   Description: This is a debugging routine for printing all of file
 * *                descriptors in a file descriptor list.
 * *   Parameters : list - a pointer to the head of an file descriptor list.
 * *   Effects    : The values of all of the file descriptors in the list are
 * *                written to stdout.
 * *   Returned   : None.
 * ***************************************************************************/
void PrintFdList(const fd_list_t *list)
{
    const fd_list_t *here;

    if (NULL == list)
    {
        printf("No fds\n");
        return;
    }

    here = list;

    printf("fds: ");

    while (here != NULL)
    {
        if (here->next != NULL)
        {
            printf("%d, ", here->fd);
        }
        else
        {
            printf("%d\n", here->fd);
        }

        here = here->next;
    }
}


int main(int argc, char* argv[]) 
{
/*
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
  	*/
	int result;
    int listenFd;   /* socket fd used to listen for connection requests */

	string fileDir = argv[2];
    struct fd_list_t *fdList, *thisFd;
    struct pollfd *pfds;
    int numFds, changed;

    /* structures for server and client internet addresses */
    struct sockaddr_in serverAddr;

    int i;

    /* argv[1] is port number, make sure it's passed to us */
    if (argc != 2)
    {
        fprintf(stderr, "Usage:  %s <port number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fdList = NULL;

    /* create server socket descriptor */
    listenFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listenFd < 0)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));     /* clear data structure */

    /* allow internet connection from any address on port argv[1] */
    serverAddr.sin_family = AF_INET;                /* internet address family */
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* any incoming address */
    serverAddr.sin_port = htons(atoi(argv[1]));     /* port number */

    /* bind to the local address */
    result = bind(listenFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    if (result < 0)
    {
        /* bind failed */
        perror("Error binding socket");
        close(listenFd);
        exit(EXIT_FAILURE);
    }

    /* listen for incoming connections */
    result = listen(listenFd, MAX_BACKLOG);

    if (result < 0)
    {
        /* listen failed */
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    /* listenFd is our only fd when we start */
    numFds = 1;
    changed = 1;
    pfds = NULL;

/*	char buffer[1024] = {0};
  	valread = read( newsockfd , buffer, 1024); 
    printf("%s\n",buffer ); 
*/ 



while (1)
    {
        int startingFds = numFds;

        if (changed)
        {
            /* one or more fds changed.  we need to change the polling struct */

            if (NULL != pfds)
            {
                free(pfds);
            }

            pfds = (struct pollfd *)malloc(numFds * sizeof(struct pollfd));

            if (NULL == pfds)
            {
                perror("Error allocating fds for poll");
                break;
            }

            /* listen fd goes in slot 0, just because */
            pfds[0].fd = listenFd;
            pfds[0].events = POLLIN;

            /* now poll for input from the rest of the sockets */
            thisFd = fdList;
            for(i = 1; i < numFds; i++)
            {
                pfds[i].fd = thisFd->fd;
                pfds[i].events = POLLIN;
                thisFd = thisFd->next;
            }

            changed = 0;
        }

        /* block on poll until something needs servicing */
        if (-1 ==  poll(pfds, numFds, -1))
        {
            perror("Error poll failed");
            exit(EXIT_FAILURE);
        }

        /* one or more fds need servicing */
        if (pfds[0].revents & POLLIN)
        {
            /* listening socket we got a new connection request */
            int acceptedFd;     /* fd for accepted connection */

            /* accept the connection; we don't care about the address */
            acceptedFd = accept(listenFd, NULL, NULL);

            if (acceptedFd < 0)
            {
                /* accept failed.  keep processing */
                perror("Error accepting connections");
            }
            else
            {
                printf("New connection on socket %d.\n", acceptedFd);
                InsertFd(acceptedFd, &fdList);
                numFds++;
                changed = 1;
            }
        }

        for(i = 1; i < startingFds; i++)
        {
            /* one or more clients needs servicing */
            if (pfds[i].revents & POLLIN)
            {
                /* service this client */
                result = DoEcho(pfds[i].fd, fdList, fileDir);
                

                if (result <= 0)
                {
                    /* socket closed normally or failed */

                    close(pfds[i].fd);
                    RemoveFd(pfds[i].fd, &fdList);
                    numFds--;
                    changed = 1;

                }
            }
        }
    }
    return 0;
}
