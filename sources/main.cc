#include <iostream>
#include <vector>

#include "../includes/game.hh"
#include "../includes/safety.hh"
#include "../includes/real.hh"

int main(int argc, char * argv[]) {

	std::vector<std::string> real_players;

	real_players.push_back("Aziz"); 
	real_players.push_back("Thomas");
	real_players.push_back("Ludovic");
	real_players.push_back("Eugène");
	// real_players.push_back("Marc");
	// real_players.push_back("Théo");

	Game g1(4, real_players);

	g1.play();

	return 0;
}
