#include <sys/types.h>   // definitions of a number of data types used in socket.h and netinet/in.h
#include <sys/socket.h>  // definitions of structures needed for sockets, e.g. sockaddr
#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in

// States
const int CLIENT_0_READY = 1;
const int CLIENT_1_READY = 2;
const int BOTH_CLIENTS_READY = 3;

// Game constants
const int NUMBER_OF_PLAYERS = 2;
const int MAX_BUFFER_SIZE = 100;


class TCPServer 
{
    public:
        ~TCPServer();
        TCPServer(int port);
        void loop();

    private:
        // GAME STUFF
        int status_;
        // Struct for holding client information
        struct client 
        {
            int id;
            int fd;
            int velocity;
            bool waiting;
        };
        client clients[NUMBER_OF_PLAYERS];


        // SOCKET STUFF
        int srvsock_;
        int port_;
        struct sockaddr_in serv_addr_, cli_addr_;
        socklen_t clilen_;

        // TODO 
        //bool check_format(std::string client_msg, int fd);
};