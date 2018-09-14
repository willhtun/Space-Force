#include <sys/types.h>   // definitions of a number of data types used in socket.h and netinet/in.h
#include <sys/socket.h>  // definitions of structures needed for sockets, e.g. sockaddr
#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in

class TCPServer 
{
    public:
        void setup(int port);
        void receive();

    private:
        int sockfd_;
        int port_;
        struct sockaddr_in serv_addr_, cli_addr_;
        socklen_t clilen_;

};
