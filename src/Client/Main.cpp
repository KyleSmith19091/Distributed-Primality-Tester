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
            client.sendMessageToServer(std::string(input));
        } else {
            std::cout << "Invalid Input\n";
        }

    }


    return 0;
}
