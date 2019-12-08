#include <iostream>
#include <vector>

#include "../includes/card.hh"
#include "../includes/safety.hh"
#include "../includes/defuser.hh"
#include "../includes/bomb.hh"

#include "../includes/player.hh"
#include "../includes/real.hh"
#include "../includes/weak.hh"
#include "../includes/strong.hh"

#include "../includes/game.hh"


int main(int argc, char * argv[]) {

	std::vector<std::string> players;

	players.push_back("Aziz"); 
	players.push_back("Thomas");
	players.push_back("Ludovic");
	players.push_back("Eugène");

	Game g1(6, players);

	std::cout << g1.to_string();

	return 0;
}
