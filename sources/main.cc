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

	Game g1(4);
	g1.fill_deck();

	std::cout << g1.to_string();

	return 0;
}
