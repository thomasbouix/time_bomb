#include "../includes/real.hh"

Real::Real() : Player() {}

Real::Real(int c, std::string n) : Player(c, n) {}

void Real::draw() {

	// Implémenter un tirage automatique
	
	std::cout << "Auto draw !\n";
}

void Real::draw(Player* p, int card) {

	// Implémenter un tirage ciblé

	std::cout << "Targeted draw !\n";
}
