#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in
#include <string>

class TCPClient 
{
    public:
        void setup(std::string hostname, int port);
        void send();

    private:
        int sockfd_;
        int port_;
        struct sockaddr_in serv_addr_;
        struct hostent *server_;  // contains tons of information, including the server's IP address
};

