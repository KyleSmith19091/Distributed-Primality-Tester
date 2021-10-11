#include <iostream>
#include <thread>
#include <vector>

#include "../include/Client.hpp"
#include "../include/Server.hpp"
#include "../include/PrimalityTester.hpp"

using namespace std;

int main(){

    Server server;
    Client client;
    PrimalityTester tester;

    const auto processor_count = std::thread::hardware_concurrency();
    std::vector<std::thread> threadPool;

    server.startServer();

    return 0;
}

