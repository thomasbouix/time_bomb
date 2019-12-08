#pragma once
#include <vector>
#include "card.hh"

#define BLUE 0
#define RED 1

class Player {

	protected :
		int color;
		std::string name;
		std::vector<Card*> deck; 

	public :
		Player();								// Instanciation aléatoire, utile pour les BOT
		Player(int color, std::string name);

		std::string get_name(void) const;

		virtual void draw(void) = 0;			// Tirage automatique, (utile pour BOT ou REAL si temps expiré)
		void draw(Player * p, int card);		// Tirage ciblé sur un joueur définis

		void add_card(Card* card);				// Ajoute une carte au deck
		void remove_card(int card);				// Supprime une carte du deck 
		void clear_deck();						// Vide le deck du joueur

		std::string to_string(void);
};
