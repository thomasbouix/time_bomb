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
		virtual ~Player();

		std::string get_name(void) const;

		virtual void draw(void) = 0;			// Tirage automatique chez un autre joueur (utile pour BOT ou REAL si temps expiré)
		void draw(Player * p, int card);		// Tirage ciblé sur un autre joueur spécifié

		void add_card(Card* card);				// Ajoute une carte à son propre deck
		void remove_card(int card);				// Supprime une carte de son propre deck 
		void clear_deck();						// Vide son propre deck

		Card* get_card(int card);				// Renvoie un pointeur sur une carte de son propre deck 

		std::string to_string(void);
};
