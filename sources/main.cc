#include <iostream>
#include <vector>

#include "../includes/card.hh"
#include "../includes/safety.hh"
#include "../includes/defuser.hh"
#include "../includes/bomb.hh"

#include "../includes/player.hh"
#include "../includes/real.hh"

void display_vec(std::vector<Card*> v) {

	for (std::vector<Card*>::iterator it = v.begin(); it != v.end(); it++) {
		std::cout << (*it)->to_string() << " / " ;
	}
	std::cout << "\n====================\n";
}

int main(int argc, char * argv[]) {

	/* ===========TEST CARD=========== */

	Safety s1;
	Defuser d1;
	Bomb b1;

	// std::vector<Card*> full_deck;

	// full_deck.push_back(&s1);
	// full_deck.push_back(&d1);
	// full_deck.push_back(&b1);

	// display_vec(full_deck);

	// full_deck.erase(full_deck.begin()+2);

	// display_vec(full_deck);

	/* ===========TEST PLAYER=========== */

	Real aziz(RED, "Aziz");
	Real thomas(BLUE, "Thomas");

	thomas.add_card(&s1);
	thomas.add_card(&d1);
	thomas.add_card(&b1);

	thomas.to_string();

	aziz.draw((Player*) &thomas, 1);	// ERREUR

	// thomas.to_string();

	return 0;
}
