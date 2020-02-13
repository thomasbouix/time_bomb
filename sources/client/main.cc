#include <iostream>
#include <vector>
#include <unistd.h>
#include "../../includes/client/game.hh"


int main(int argc, char * argv[]){

	if (argc != 6) {
		std::cout << "error in arguments : " << std::endl;
		std::cout << "<server ip> <server port> <client ip> <client port> <name>" << std::endl;
		exit(0);
	}

	std::string server_ip(argv[1]);
	std::string client_ip(argv[3]);

	int server_port,client_port;
	std::string str_serv(argv[2]);
	std::string str_cli(argv[4]);
	server_port = std::stoi(str_serv);
	client_port = std::stoi(str_cli);

	std::string name(argv[5]);

	std::cout << server_ip << std::endl;
	std::cout << server_port << std::endl;
	std::cout << client_ip << std::endl;
	std::cout << client_port << std::endl;
	std::cout << name << std::endl;

	Game* game = new Game(name,client_port,server_port,client_ip,server_ip);

	(*game).play();

	delete game;

	return 0;
}
