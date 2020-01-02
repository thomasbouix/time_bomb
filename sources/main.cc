#include <iostream>
#include <vector>

#include "../includes/game.hh"
#include "../includes/safety.hh"
#include "../includes/real.hh"

std::string global_buffer;

int main(int argc, char * argv[]) {
/*
	std::vector<std::string> real_players;

	real_players.push_back("aziz");
	real_players.push_back("thomas");
	real_players.push_back("ludovic");
	real_players.push_back("eugène");
	// real_players.push_back("marc");
	// real_players.push_back("théo");
*/
	//Game g1(6, real_players);

	//std::string message("aziz: draw thomas 1");

	//g1.draw(message);
	Game g1(4);
	g1.play();

	return 0;
}
