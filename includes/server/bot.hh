#pragma once
#include "player.hh"

class Bot : public Player {

	public :
		Bot();
		Bot(int c);		// Permet à GAME de choisir une couleur
};
