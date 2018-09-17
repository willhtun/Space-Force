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
#include <boost/lexical_cast.hpp>

#include <string>

// States
const int CLIENT_0_READY = 1;
const int CLIENT_1_READY = 2;
const int BOTH_CLIENTS_READY = 3;

// Game constants
const int NUMBER_OF_PLAYERS = 2;
const int MAX_BUFFER_SIZE = 100;

// Struct for holding client information
struct client 
{
    int id;
    int fd;
    int velocity;
    bool waiting;
};

class TCPServer 
{
    public:
        ~TCPServer(){ close( srvsock_);}
        TCPServer(int port);
        void loop();

    private:
        // Game stuff
        int status_;
        client clients[NUMBER_OF_PLAYERS];

        // Socket stuff
        int srvsock_;
        int port_;
        struct sockaddr_in serv_addr_, cli_addr_;
        socklen_t clilen_;

        // TODO 
        //bool check_format(std::string client_msg, int fd);
};

TCPServer::TCPServer(int port)
{
    // Initial game values
    status_ = 0;
    clients[0].waiting = false;
    clients[1].waiting = false;

    srvsock_ = socket(AF_INET, SOCK_STREAM, 0);  // create socket
    if ( srvsock_ < 0)
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

    if (bind( srvsock_, (struct sockaddr *) &serv_addr_, sizeof(serv_addr_)) < 0)
    {
        std::cout << "Error. Could not bind" << std::endl;
        exit(1);
    }

    listen( srvsock_, 5);  // 5 simultaneous connection at most
}


void TCPServer::loop()
{
  fd_set active_fd_set, read_fd_set;
  int n_bytes, maxfd;
  struct sockaddr_in clientname;
  size_t size;
  char buffer[MAX_BUFFER_SIZE+1];


  /* Initialize the set of active sockets. */
  FD_ZERO(&active_fd_set);
  FD_SET(srvsock_, &active_fd_set);
  maxfd = srvsock_;

  while (1)
    {
        // If both clients are waiting, send message to start
        if (clients[0].waiting && clients[1].waiting)
        {
            std::string msg("ready");
            n_bytes = send(clients[0].fd,msg.c_str(), msg.length(), 0);  
            n_bytes = send(clients[1].fd, msg.c_str(), msg.length(), 0); 
            clients[1].waiting = false;
            clients[0].waiting = false;

        }

        // Both clients are ready for opponents velocity
        if (BOTH_CLIENTS_READY == status_)
        {
            char buffer[100];
            memset(buffer,0, 100);

            int to_send = sprintf(buffer, "V0s: %d,%d", clients[0].velocity, clients[1].velocity);
            int n_bytes = send(clients[0].fd, buffer, to_send, 0);  

            to_send = sprintf(buffer, "V0s: %d,%d", clients[1].velocity, clients[0].velocity);
            n_bytes = send(clients[1].fd, buffer, to_send, 0); 
            
            // TODO
            // Keep connection open for longer games/replaying
            break;
        }

        /* Block until input arrives on one or more active sockets. */
        read_fd_set = active_fd_set;

        struct timeval timeout;
        timeout.tv_sec  = 1;
        timeout.tv_usec = 0;

        int result = select (maxfd+1, &read_fd_set, NULL, NULL, &timeout);

        // ERROR
        if (result < 0)
        {
            perror ("select");
            exit (EXIT_FAILURE);
        }
        // TIMEOUT
        else if (result == 0)
        {
            if (status_ != BOTH_CLIENTS_READY)
            {
                std::string msg("waiting");
                int n_bytes = send(clients[0].fd,msg.c_str(), msg.length(), 0);  
                n_bytes = send(clients[1].fd, msg.c_str(), msg.length(), 0); 
            }
        }

        // OTHERWISE Service all the sockets with input pending
        for (int i = 0; i < maxfd + 1; ++i)
            if (FD_ISSET (i, &read_fd_set))
            {
                if (i == srvsock_)
                {
                    /* Connection request on original socket. */
                    int newfd;
                    size = sizeof (clientname);
                    newfd = accept(srvsock_, (struct sockaddr *) &cli_addr_, &clilen_);

                    if (newfd < 0)
                    {
                        perror ("accept");
                        exit (EXIT_FAILURE);
                    }
                    maxfd = (maxfd < newfd) ? newfd : maxfd;   // Set new max 

                    FD_SET (newfd, &active_fd_set);

                    if (i > 5) exit(1);
                    int clientid = newfd - 4;
                    clients[clientid].id = clientid;
                    clients[clientid].fd = newfd;
                    clients[clientid].waiting = true;
                }
                else
                {
                    int clientid = i - 4;

                    /* Data arriving on an already-connected socket. */
                    if ((result = recv(i, buffer, MAX_BUFFER_SIZE, 0)) < 0)
                        {
                            perror("recv");
                            exit(EXIT_FAILURE);
                        }
                    std::string request(buffer,result);

                    //Format V0: <vel> where <vel> is a double digit number
                    clients[clientid].velocity = boost::lexical_cast<int>(request.substr(4,2));

                    if(clientid == 0) status_ += CLIENT_0_READY;
                    if(clientid == 1) status_ += CLIENT_1_READY;
                    FD_CLR (i, &active_fd_set);
                }
            }
    }
}

// bool TCPServer::check_format(std::string client_msg, int fd)
// {
//     //TODO: Check it is a valid client message
//     std::cout << client_msg.substr(0, 3) << std::endl;
//     if(client_msg.substr(0, 3) != std::string("V0:"))
//         {
//             std::cerr << "Received message in wrong format" << std::endl;
//             std::string response("Wrong format");
//             int n = send(fd, response.c_str(), response.length(), 0);
//             if (n < 0) std::cerr << "Could not send" << std::endl;
//             return false;
//         }
//     return true;
// }


int main(int argc, char *argv[])
{
    TCPServer server(1101);
    server.loop();

return 0;
}
