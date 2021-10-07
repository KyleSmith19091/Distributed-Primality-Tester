#ifndef SERVER_HPP 
#define SERVER_HPP

#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <csignal>
#include <Logging/Logger.hpp>
#include <iostream>

class Server{
    private:
        constexpr static u_int16_t PORT = 8080;
        const int addressLength = sizeof(address);
        struct sockaddr_in address;
        int serverFD;

        std::string readDataFromClient(const int&);
        void writeDataToClient(const int& newSocket, const std::string&);
        static void signalHandler(int);

    public:
        Server();
        ~Server();
    
        void startServer();

};	
#endif
