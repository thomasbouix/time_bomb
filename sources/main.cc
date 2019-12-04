#include <iostream>
#include <vector>

#include "../includes/card.hh"
#include "../includes/safety.hh"
#include "../includes/defuser.hh"
#include "../includes/bomb.hh"

int main(int argc, char * argv[]) {

	Safety s1;
	Defuser d1;
	Bomb b1;

	std::vector<Card*> full_deck;

	full_deck.push_back(&s1);
	full_deck.push_back(&d1);
	full_deck.push_back(&b1);

	for (std::vector<Card*>::iterator it = full_deck.begin(); it != full_deck.end(); it++) {
		std::cout << (*it)->to_string();
	}

	return 0;
}
