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

int main(int argc, char * argv[]) {

	// CARDS
	Safety s1;
	Defuser d1;
	Bomb b1;

	// PLAYERS
	Real aziz(RED, "Aziz");
	Real thomas(BLUE, "Thomas");

	thomas.add_card(&s1);
	thomas.add_card(&d1);
	thomas.add_card(&b1);

	std::cout << thomas.to_string();

	// aziz.draw(&thomas, 1);
	// aziz.draw(&thomas, 1);
	// aziz.draw(&thomas, 0);

	std::cout << thomas.to_string();

	Weak w1(RED);
	std::cout << w1.to_string();

	w1.draw(&thomas, 0);

	Strong str1(BLUE);
	std::cout << str1.to_string();
	str1.draw(&thomas, 0);

	return 0;
}
