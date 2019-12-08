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
	real_players.push_back("Marc");

	Game g1(6, real_players);

	g1.deal();

	std::cout << g1.to_string();

	return 0;
}
