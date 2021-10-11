#include <iostream>
#include <string>
#include "../../include/Client.hpp"

using namespace std;

int main(){

    Client client;
    std::string input("");
    
    while(1) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if(input.length() > 0) {
            client.sendMessageToServer(input);
            std::string buffer = client.readMessageFromServer();

            if(buffer.length() == 0) {
                exit(0);
            }
            //client.readMessageFromServer();
        } else {
            std::cout << "Invalid Input\n";
        }
    }


    return 0;
}
