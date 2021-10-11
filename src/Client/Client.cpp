#include "../../include/Client.hpp"

Client::Client() {
    clientSocket = -1;
}

Client::~Client() {}

// Connect client socket to the server socket address
void Client::connectToServer() {

    createSocket();

    if((connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)) {
        std::cout << Log::Critical() << "Could not connect to Server\n";
        exit(EXIT_FAILURE);
    };

    std::cout << Log::Info() << "Connected to server!\n";
}

void Client::createSocket() {
    // Create socket
    if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << Log::Error() << "Could not create Client Socket!\n";
    }

    memset(&serverAddress, '0', sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0)
    {
        std::cout << Log::Error() << "Invalid Address, Address is not supported\n";
        exit(EXIT_FAILURE);
    }

    std::cout << Log::Info() << "Done Creating a Client Socket!\n";
}

// Sending string data to server
void Client::sendMessageToServer(const std::string& message) {
    connectToServer();
    write(clientSocket, message.c_str(), message.length());
    std::cout << Log::Info() << "Message sent to Server\n";
}

// Reading string data from server
std::string Client::readMessageFromServer() {
    char buffer[READ_BUFFER_SIZE] = {0};
    read(clientSocket, buffer, READ_BUFFER_SIZE);
    return std::string(buffer);
}
