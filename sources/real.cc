#include "../includes/real.hh"

Real::Real() : Player() {}

Real::Real(int c, std::string n) : Player(c, n) {}

void Real::draw() {

	// Implémenter un tirage automatique
	// Besoin de la liste des joueurs dans GAME pour cela
	
	std::cout << "Auto draw !\n";
}
