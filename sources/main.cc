#include <iostream>
#include <vector>

#include "../includes/card.hh"
#include "../includes/safety.hh"
#include "../includes/defuser.hh"
#include "../includes/bomb.hh"

#include "../includes/player.hh"
#include "../includes/real.hh"

int main(int argc, char * argv[]) {

	/* ===========TEST CARD=========== */

	Safety s1;
	Defuser d1;
	Bomb b1;

	std::vector<Card*> full_deck;

	full_deck.push_back(&s1);
	full_deck.push_back(&d1);
	full_deck.push_back(&b1);

	// for (std::vector<Card*>::iterator it = full_deck.begin(); it != full_deck.end(); it++) {
	// 	std::cout << (*it)->to_string();
	// }

	/* ===========TEST PLAYER=========== */

	Real r1;
	Real r2(BLEU, "Thomas");

	std::cout << r1.get_name() << std::endl;
	std::cout << r2.get_name() << std::endl;
 
	r1.draw();
	r1.draw(&r2, 3);

	return 0;
}
