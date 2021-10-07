#ifndef CLIENT_HPP 
#define CLIENT_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>

#include <Logging/Logger.hpp>

class Client{
    private:

        constexpr static u_int16_t PORT = 8080;
        constexpr static u_int16_t READ_BUFFER_SIZE = 1024;

        int clientSocket;
        struct sockaddr_in serverAddress;
        void connectToServer();

    public:
        Client();
        ~Client();

        void sendMessageToServer(const std::string&);
        std::string readMessageFromServer();
};	
#endif
