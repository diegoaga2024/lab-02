/* A simple server in the internet domain using TCP
 * Answer the questions below in your writeup
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    /* 1. What is argc and *argv[]?
     An integer and a pointer to a list, which represent the port number and the IP respectively. The IP is  needed to identify the device on the network. The port number is 16-bit unsigned integer that specifies the logical endpoint of the server.  
     
     */
    int sockfd, newsockfd, portno;
    /* 2. What is a UNIX file descriptor and file descriptor table?
     A file descriptor is a unique non-negative integer assigned by the operating system to a process, which is used to refer to an open file. The file descriptor table, which is used to keep track of all the open files that the process has access to. It provides a convenient and efficient mechanism for processes to access the files they need
     */
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;
    /* 3. What is a struct? What's the structure of sockaddr_in?
     	A struct groups together different values to form a single entity. The structure of sockaddr_in declares two unitiliazed variablies which aregoing to represent the server address and the client address. These each have an address family, a port number, an internet address, and padding for sizing.
     */
    
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /* 4. What are the input parameters and return value of socket()
     The first input parameter of socket() are the address family which is set to AF_INET for internet protocol. The second input parameter is the sock_stream socket. This socket uses a reliable, stream-oriented protocol to ensure that data is transmitted in the order it was sent, without loss or duplication. The third input specifies that the system should choose the default protocol '0' for the specified address family and socket type.
     */
    
    if (sockfd < 0) 
       error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             error("ERROR on binding");
    /* 5. What are the input parameters of bind() and listen()?
    The input parameters for the bind function are the socket file descriptor sockfd and a pointer to a sockaddr_in structure. The input for the listen function is the socket file descriptor. The listen function's second input parameter is the backlog queue size, which determines the maximum number of incoming connections that can be queued up waiting to be accepted by the server. In this case that number is 5.
     */
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    
    while(1) {
        /* 6.  Why use while(1)? Based on the code below, what problems might occur if there are multiple simultaneous connections to handle?
        Without the while loop, the server would only be able to handle a single client connection, after which it would terminate. Based on the code below each new incoming connection may cause the server to create new resources such as memory, file descriptors, or threads, which can eventually lead to resource exhaustion and the server crashing.
        */
        
	char buffer[256];
        newsockfd = accept(sockfd, 
                    (struct sockaddr *) &cli_addr, 
                    &clilen);
	/* 7. Research how the command fork() works. How can it be applied here to better handle multiple connections?
         The fork() command is a child proccess to the parent process accept(). This means that after the successful completion of a call to the accept() function, the server can call fork() to handls the incoming connection while the parent process continues to listen for new connections. This can be applied here to handle multiple connections in parallel by handling the processing of each connection independently. This can improve the TCP server's performance and responsiveness.
         */
        
	if (newsockfd < 0) 
             error("ERROR on accept");
	bzero(buffer,256);
        
	n = read(newsockfd,buffer,255);
        if (n < 0) 
            error("ERROR reading from socket");
        printf("Here is the message: %s\n",buffer);
        n = write(newsockfd,"I got your message",18);
        if (n < 0) 
            error("ERROR writing to socket");
        close(newsockfd);
    }
    close(sockfd);
    return 0; 
}
  
/* This program makes several system calls such as 'bind', and 'listen.' What exactly is a system call?
	A system call is a request made by a user-level program to the operating system or to a specific system component. TCP system calls are used to create and manage sockets, bind addresses to sockets, listen for incoming connections, accept incoming connections, read and write data, and close connections.
 */
