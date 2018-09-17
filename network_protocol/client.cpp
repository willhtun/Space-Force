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


void TCPClient::setup(std::string hostname, int port)
{   
    flags_ = 0;
    port_ = port;

    // create a new socket
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);  
    if (sockfd_ < 0)
    {
       fprintf(stderr,"Error opening socket");
       exit(0);
    }

    // get server informations
    server_ = gethostbyname(hostname.c_str());  
    if (server_ == NULL) 
    {
        fprintf(stderr,"No such host\n");
        exit(0);
    }

    memset((char *) &serv_addr_, 0, sizeof(serv_addr_));
    serv_addr_.sin_family = AF_INET; //initialize server's address
    bcopy((char *)server_->h_addr, (char *)&serv_addr_.sin_addr.s_addr, server_->h_length);
    serv_addr_.sin_port = htons(port_);

    //establish a connection to the server
    if (connect(sockfd_,(struct sockaddr *)&serv_addr_,sizeof(serv_addr_)) < 0) 
    {
       fprintf(stderr,"Error connecting to socket");
       exit(0);
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
    std::string response = std::string(buffer_,n_bytes);
    return (response != ready_string);
}

void TCPClient::send_message(std::string msg)
{
    int n_bytes = send(sockfd_, msg.c_str(), msg.length(), flags_);  
    if (n_bytes < 0)
    {
       fprintf(stderr,"Error writing to socket");
       exit(0);
    }
}
int TCPClient::send_velocity(int vel)
{
    char buffer[32];
    int n = sprintf(buffer, "V0: %d", vel);
    send_message(std::string(buffer,n));
    return 0;
}



int TCPClient::get_opponents_velocity()
{
    memset(buffer_,0, BUFFER_SIZE);

    int n_bytes = recv(sockfd_,buffer_, BUFFER_SIZE, 0);  // read from the socket
    std::cout << buffer_ << std::endl;

    if (n_bytes < 0)
    {
       fprintf(stderr,"Error reading to socket");
       exit(0);
    }
    
    std::string response(buffer_,n_bytes);
    int i = 0;
    for(char& c : response) {
        if (c == 'V') break;
        i++;
    }
    int opp_vel = boost::lexical_cast<int>(response.substr(i+5,2));
    return opp_vel;
}

int main(int argc, char *argv[])
{
    TCPClient client;
    client.setup("localhost", 1101);
    while(client.is_ready())
        std::cout << "waiting" << std::endl;

    client.send_velocity(boost::lexical_cast<int>(argv[1]));

    // std::cout << "Enter message: " << std::endl;
    // std::cin >> msg;

    int o_vel = client.get_opponents_velocity();

    // Print out repsonse
    std::cout << "Opponents velocity: "<< o_vel << std::endl;



    return 0;
}
