#pragma once
#include <vector>
#include "card.hh"

#define BLEU 0
#define ROUGE 1

class Player {

	protected :
		int color;
		std::string name;
		std::vector<Card*> deck; 

	public :
		Player();										// Instanciation aléatoire, utile pour les BOT
		Player(int color, std::string name);

		std::string get_name(void) const;

		virtual void draw(void) = 0;					// Tirage auto, utile pour les bot ou qd le temps d'un joueur expire
		virtual void draw(Player * p, int card) = 0;	// Tirage ciblé
};
