#include "../../include/Server.hpp"
#include <Logging/Logger.hpp>

Server::Server() {
    
    // Create Socket file descriptor 
    if ((serverFD = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cout << Log::Error() << "Failed Creating Socket fd\n"; 
        exit(EXIT_FAILURE);
    }

    int opt = 1;

    // Set Server socket to allow for multiple connections
    if(setsockopt(serverFD, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0) {
        std::cout << Log::Error() << "Could not set socket option to accept multiple client connections\n";
        exit(EXIT_FAILURE);
    }

    // Define socket attributes
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->PORT);
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    // Bind socket to localhost and port
    if (bind(serverFD, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cout << Log::Error() << "Failed to  bind socket\n";
        exit(EXIT_FAILURE);
    }

    // Listen for max of 10 incoming connections
    if (listen(serverFD, 10) < 0) {
        std::cout << Log::Error() << "Failed to listen on PORT: " << this->PORT;
        exit(EXIT_FAILURE);
    }

    std::cout << Log::Info() << "Server Sokcet Creation Done!\n";
    std::cout << Log::Info() << "Waiting for connections...\n";
}

Server::~Server() {
    std::cout << Log::Warning() << "Destructing Server\n";
}

std::string Server::readDataFromClient(const int& newSocket) {
    char buffer[30000] = {0};
    int inputLength = read(newSocket, buffer, 30000);
    return inputLength > 0 ? std::string(buffer) : std::string("");
}

void Server::writeDataToClient(const int& newSocket, const std::string& writeData) {
    std::cout << Log::Info() << "Writing Data to Client\n";
    write(newSocket, writeData.c_str(), writeData.length()) < 0 ?
        std::cout << Log::Error() << "Could not write data to client\n" :
        std::cout << Log::Info() << "Data Sent to client\n";
}

void Server::startServer() {

    int newSocket = 0;

    while(1) {
            if((newSocket = accept(serverFD, (struct sockaddr *)&address, (socklen_t*)&addressLength)) < 0) {
                std::cout << Log::Error() << "Failed to accept incoming Socket connection\n";
            }

            std::cout << Log::Info() << "New Connection: [Socket=" << newSocket << "] [IP=" << inet_ntoa(address.sin_addr) << "] [PORT=" 
                << ntohs(address.sin_port) << "]\n";
            
            std::string buffer = readDataFromClient(newSocket);

            if(buffer == "exit") {
                shutdownServer();
            }

            writeDataToClient(newSocket, "Hello World!");

            close(newSocket);
    }

}

void Server::shutdownServer() {
    close(serverFD);
    std::cout << Log::Warning() << "Shutting Down Server\n";
    exit(EXIT_SUCCESS);
}
