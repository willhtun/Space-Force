#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in
#include <string>

#define BUFFER_SIZE 256 

class TCPClient 
{
    public:
        // Setup and connect to server
        void setup(std::string hostname, int port);

        // Block until find opponent
        void find_game();

        // Send velocity to server
        int send_velocity(int vel);

        // Send message to server
        void send_message(std::string msg);

        //Wait for reponse
        int get_opponents_velocity();

        // Close socket
        ~TCPClient();

    private:
        char buffer_[BUFFER_SIZE];
        int port_, sockfd_, flags_;
        struct sockaddr_in serv_addr_;
        struct hostent *server_;  // contains tons of information, including the server's IP address
};

