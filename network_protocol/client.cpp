/*
 A simple client in the internet domain using TCP
 Usage: ./client hostname port_ (./client 192.168.0.151 10000)
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>      // define structures like hostent
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"


void TCPClient::setup(std::string hostname, int port)
{   
    port_ = port;
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);  // create a new socket
    if (sockfd_ < 0)
    {
       fprintf(stderr,"Error opening socket");
       exit(0);
    }
    server_ = gethostbyname(hostname.c_str());  // takes a string like "www.yahoo.com", and returns a struct hostent which contains information, as IP address, address type, the length of the addresses...
    if (server_ == NULL) 
    {
        fprintf(stderr,"No such host\n");
        exit(0);
    }

    memset((char *) &serv_addr_, 0, sizeof(serv_addr_));
    serv_addr_.sin_family = AF_INET; //initialize server's address
    bcopy((char *)server_->h_addr, (char *)&serv_addr_.sin_addr.s_addr, server_->h_length);
    serv_addr_.sin_port = htons(port_);

    if (connect(sockfd_,(struct sockaddr *)&serv_addr_,sizeof(serv_addr_)) < 0) //establish a connection to the server
    {
       fprintf(stderr,"Error connecting to socket");
       exit(0);
    }
}

void TCPClient::send()
{
    char buffer[256];

    printf("Please enter the message: ");
    memset(buffer,0, 256);
    fgets(buffer,255,stdin);  // read message

    int n = write(sockfd_,buffer,strlen(buffer));  // write to the socket
    if (n < 0)
    {
       fprintf(stderr,"Error writing to socket");
       exit(0);
    }

    memset(buffer,0,256);
    n = read(sockfd_,buffer,255);  // read from the socket
    if (n < 0)
    {
       fprintf(stderr,"Error reading to socket");
       exit(0);
    }

    printf("%s\n",buffer);  // print server's response

    close(sockfd_);  // close socket
}
int main(int argc, char *argv[])
{
    TCPClient client;
    client.setup("localhost", 1100);

    client.send();

    return 0;
}
