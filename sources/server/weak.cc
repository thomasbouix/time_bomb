#include "../../includes/server/weak.hh"

Weak::Weak() : Bot() {}

Weak::Weak(int c) : Bot(c) {}

void Weak::draw() {

	// Implémenter un tirage automatique spécifique à WEAK
	// Besoin de la liste des joueurs dans GAME pour cela

	std::cout << "Auto draw !\n";
}
