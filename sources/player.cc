#include "../includes/player.hh"

Player::Player() {

	srand(time(NULL));
	color = rand() % 2;

	int n = rand() % 5;

	switch (n) {
		case 0 : name = "Alfred";
			break;
		case 1 : name = "Benjamin";
			break;
		case 2 : name = "Charles";
			break;
		case 3 : name = "David";
			break;
		case 4 : name = "Edward";
			break;
		default :
			break;
	} 
}

Player::Player(int c, std::string n) : color(c), name(n) {}

std::string Player::get_name(void) const {
	return name;
}