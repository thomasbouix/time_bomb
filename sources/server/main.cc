#include <iostream>
#include <vector>

#include "../../includes/game.hh"

std::string global_buffer;

int main(int argc, char * argv[]) {

	if (argc != 3) {
		std::cout << "error : <port server> <number of player>" << std::endl;
		return -1;
	}

	int port = atoi(argv[1]);
	int n_player = atoi(argv[2]);
	
	Game g1(n_player, port);
	g1.play();

	return 0;
}
