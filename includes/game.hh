#pragma once
#include <typeinfo>
#include "player.hh"
#include "card.hh"


class Game {

	private :
		// Variables d'initialisation
		int nb_players;						// Nombre de joueurs inscrits
		int nb_blue;						// Nombre de bleus potentiels
		int nb_red;							// Nombre de rouges potentiels
		int nb_safeties;					// Safety cards à instancier
		int nb_defusers;					// Defuser cards à instancier

		// Variable de management
		std::vector<Player*> players;		// Ensemble des joueurs participants
		std::vector<Card*> full_deck;		// Ensemble des cartes restantes

		// Variables de monitoring
		int nb_round;						// Nombre de round dejà joués
		int drew_cards_rd;					// Nombre de cartes tirées dans le current round
		int def_found;						// Nombre de defuser trouvés en tout 
		Player * current_player;			// Joueur qui a la main 

	public :
		Game(int nb_players, std::vector<std::string> real_players);

		void fill_deck();											// Instancie toutes les cartes du jeu
		void fill_players(std::vector<std::string> real_players);	// Instancie tous les joueurs réels et complète avec des bots
		void deal();												// Distribue les cartes encore en jeu 

		void draw(Player* a, Player* b, int card);					// pa pioche une carte chez pb

		std::string to_string();
};