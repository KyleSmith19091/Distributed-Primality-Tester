#include "../../include/Server.hpp"

Server::Server() {

    // Register signal handler
    signal(SIGINT,signalHandler);
    
    // Create Socket file descriptor 
    if ((serverFD = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cout << Log::Error() << "Failed Creating Socket fd\n"; 
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

    std::cout << Log::Info() << "Server Sokcet Done!\n";
}

Server::~Server() {
    std::cout << Log::Warning() << "Destructing Server\n";
}

void Server::signalHandler(int signalNumber) {
    switch (signalNumber) {
        case SIGABRT:
            std::cout << Log::Warning() << "Aborting Program\n";
            exit(EXIT_SUCCESS);
            break;

        case 2:
            std::cout << Log::Warning() << "Exiting Program\n";
            exit(EXIT_SUCCESS);
            break;

        case SIGTERM:
            std::cout << Log::Warning() << "Terminating Program\n";
            exit(EXIT_SUCCESS);
            break;

        default:
            std::cout << Log::Critical() << "Strange signal received\n";
            exit(EXIT_FAILURE);
    }
}

std::string Server::readDataFromClient(const int& newSocket) {
    std::cout << Log::Info() << "Received Data From Client\n";
    char buffer[30000] = {0};
    read(newSocket, buffer, 30000);
    return std::string(buffer);
}

void Server::writeDataToClient(const int& newSocket, const std::string& writeData) {
    std::cout << Log::Info() << "Writing Data to Client\n";
    write(newSocket, writeData.c_str(), writeData.length());
}

void Server::startServer() {

    int newSocket = 0;

    while(1) {
        std::cout << Log::Info() << "Waiting For Messages\n";

        // Accept first incoming connection
        if ((newSocket = accept(serverFD, (struct sockaddr *)&address, (socklen_t*)&addressLength)) < 0) {
            std::cout << Log::Error() << "Could not accept data from client!\n";
            exit(EXIT_FAILURE);
        }

        std::cout << Log::Info() << "Accepted Socket\n";

        // Read any data sent from new client socket
        std::string clientData = readDataFromClient(newSocket);

        // Only evaluate if there is data from client
        if(clientData.length() > 0) {
            std::cout << Log::Info() << clientData << "\n"; 

            // Accept exit request from client
            if(clientData.substr(0,4) == "exit") {
                std::cout << Log::Info() << "Closing socket!\n";
                writeDataToClient(newSocket, std::string("Closing Socket"));
                close(newSocket);
                break;
            } 
            
            // Write data to client to indicate that data was received
            writeDataToClient(newSocket, std::string("Received Data"));

            std::cout << Log::Info() << "Done Receiving Messsages\n";
        }

        // Close connection with client socket
        close(newSocket);
    }

}
