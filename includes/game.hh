#pragma once
#include "player.hh"
#include "card.hh"

class Game {

	private :
		std::vector<Player*> players;
		std::vector<Card*> full_deck;

		int nb_round;									// Nombre de round dejà joués
		int drew_cards_rd;								// Nombre de cartes tirées dans le current round
		int def_found;									// Nombre de defuser trouvés en tout 
		Player * current_player;						// Joueur qui a la main 

	public :
		Game(int nb_players);

		void fill_deck();								// Instancie toutes les cartes du jeu
		void fill_players();							// Instancie tous les joueurs du jeu
		void deal();									// Distribue les cartes encore en jeu 

		void draw(Player * pa, Player * pb, int card);	// pa pioche une carte chez pb
};