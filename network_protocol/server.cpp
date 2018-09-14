/* A simple server in the internet domain using TCP
   The port number is passed as an argument
   This version runs forever, forking off a separate
   process for each connection
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>  /* signal name macros, and the kill() prototype */
#include <sys/types.h>   // definitions of a number of data types used in socket.h and netinet/in.h
#include <sys/socket.h>  // definitions of structures needed for sockets, e.g. sockaddr
#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in
#include <iostream>

#include "server.h"

void TCPServer::setup(int port)
{
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);  // create socket
    if (sockfd_ < 0)
    {
        std::cout << "Could not open socket" << std::endl;
        exit(1);
    }

    memset((char *) &serv_addr_, 0, sizeof(serv_addr_));   // reset memory

    // fill in address info
    port_ = port;
    serv_addr_.sin_family = AF_INET;
    serv_addr_.sin_addr.s_addr = INADDR_ANY;
    serv_addr_.sin_port = htons(port_);

    if (bind(sockfd_, (struct sockaddr *) &serv_addr_, sizeof(serv_addr_)) < 0)
    {
        std::cout << "Error. Could not bind" << std::endl;
        exit(1);
    }
    listen(sockfd_, 5);  // 5 simultaneous connection at most
}

void TCPServer::receive()
{
    //accept connections
    int newsockfd = accept(sockfd_, (struct sockaddr *) &cli_addr_, &clilen_);

    if (newsockfd < 0)
    {
        std::cout << "Error. Could not accept()" << std::endl;
        exit(1);
    }
    int n;
    char buffer[256];

    memset(buffer, 0, 256);  // reset memory

    //read client's message
    n = read(newsockfd, buffer, 255);
    if (n < 0)
    {
        std::cout << "Error reading from socket" << std::endl;
        exit(1);
    } 
    printf("Here is the message: %s\n", buffer);

    //reply to client
    n = write(newsockfd, "I got your message", 18);
    if (n < 0)     
    {
        std::cout << "Error writing to socket" << std::endl;
        exit(1);
    }

    close(newsockfd);  // close connection
    close(sockfd_);
}

int main(int argc, char *argv[])
{
    TCPServer server;
    server.setup(1100);
    server.receive();
    return 0;
}
