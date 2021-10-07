run: 
	g++ -O2 -std=c++11 ./src/Main.cpp ./src/Server/Server.cpp ./src/Client/Client.cpp ./src/PrimalityTest/PrimalityTester.cpp -o ./build/main
	./build/main

server:
	g++ -std=c++11 ./src/Server/*.cpp -I ./include -o ./build/server
	./build/server

client:
	g++ -std=c++11 ./src/Client/*.cpp -I ./include -o ./build/client
	./build/client
