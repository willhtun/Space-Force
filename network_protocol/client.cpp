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
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "client.h"


TCPClient::TCPClient(std::string hostname, int port)
{   
    flags_ = 0;
    port_ = port;

    // create a new socket
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);  
    if (sockfd_ < 0)
    {
       fprintf(stderr,"Error opening socket");
       exit(EXIT_FAILURE);
    }

    // get server informations
    server_ = gethostbyname(hostname.c_str());  
    if (server_ == NULL) 
    {
        fprintf(stderr,"No such host\n");
        exit(EXIT_FAILURE);
    }

    memset((char *) &serv_addr_, 0, sizeof(serv_addr_));
    serv_addr_.sin_family = AF_INET; //initialize server's address
    bcopy((char *)server_->h_addr, (char *)&serv_addr_.sin_addr.s_addr, server_->h_length);
    serv_addr_.sin_port = htons(port_);

    //establish a connection to the server
    if (connect(sockfd_,(struct sockaddr *)&serv_addr_,sizeof(serv_addr_)) < 0) 
    {
       fprintf(stderr,"Error connecting to socket");
       exit(EXIT_FAILURE);
    }
}

TCPClient::~TCPClient()
{
    close(sockfd_);  // close socket
}

bool TCPClient::is_ready()
{
    std::string ready_string("ready");
    int n_bytes = recv(sockfd_,buffer_, BUFFER_SIZE, 0); 
    if (n_bytes < 0)
    {
       fprintf(stderr,"Error reading to socket");
       exit(EXIT_FAILURE);
    }
    std::string response = std::string(buffer_,n_bytes);
    return (response != ready_string);
}


int TCPClient::send_velocity(int vel)
{
    memset(buffer_,0, BUFFER_SIZE);

    int to_send = sprintf(buffer_, "V0: %d", vel);
    
    int n_bytes = send(sockfd_, buffer_, to_send, flags_);  
    if (n_bytes < 0)
    {
       fprintf(stderr,"Error writing to socket");
       exit(EXIT_FAILURE);
    }
    return 0;
}


//TODO: Make parser error proof
int TCPClient::get_opponents_velocity()
{
    memset(buffer_,0, BUFFER_SIZE);

    int n_bytes = recv(sockfd_,buffer_, BUFFER_SIZE, 0); 
    if (n_bytes < 0)
    {
       fprintf(stderr,"Error reading to socket");
       exit(EXIT_FAILURE);
    }
    
    std::string response(buffer_,n_bytes);
    int opp_vel = stoi(response.substr(5,2));
    return opp_vel;
}



// EXAMPLE CODE
// This code shows how to interface with the client
int main(int argc, char *argv[])
{   
    if (argc != 4 )
        std::cout << "Usage: ./client <hostname> <port> <velocity>" << std::endl;

    // Init client
    TCPClient client(argv[1], atoi(argv[2]));

    // Block until two clients have connected
    while(client.is_ready())  std::cout << "waiting" << std::endl;

    // Send velocity to server
    int velocity_to_send = atoi(argv[1]);
    client.send_velocity(velocity_to_send);

    // Get opponents velocity 
    int o_vel = client.get_opponents_velocity();
    std::cout << "Opponents velocity: "<< o_vel << std::endl;

    return 0;
}
