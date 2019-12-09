#pragma once
#include <typeinfo>
#include "player.hh"
#include "card.hh"

class Game {

	private :
		// Container
		std::vector<Player*> players;		// Ensemble des joueurs participants
		std::vector<Card*> full_deck;		// Ensemble des cartes restantes

		// Variables d'initialisation
		int nb_players;						// Nombre de joueurs (Real + Bot)
		int nb_blue;						// Nombre de bleus potentiels
		int nb_red;							// Nombre de rouges potentiels
		int nb_safeties;					// Safety cards à instancier
		int nb_defusers;					// Defuser cards à instancier

		// Variables de management
		int nb_round;						// Nombre de round dejà joués
		int drew_cards_rd;					// Nombre de cartes tirées dans le current round
		int def_found;						// Nombre de defuser trouvés en tout 
		int bomb_found;
		Player * next_player;				// Joueur qui a la main 

	public :
		Game(int nb_players, std::vector<std::string> real_players);
		~Game();

		void fill_deck();											// Instancie toutes les cartes du jeu 
		void fill_players(std::vector<std::string> real_players);	// Instancie tous les joueurs réels et complète avec des bots
		void deal();												// Distribue les cartes encore en jeu, actualise nb_round, drew_cards_rd

		bool draw(Player* a, Player* b, int card);					// pa pioche une carte chez pb, puis deal() si fin du round
		bool test_draw(int a, int b, int c);						// draw avec des indices, utilise game::draw(Player*, Player*, int)
		bool play_draw(Player* nxt, std::string target, int card);	// fonction qu'utilise game::play()

		std::string to_string();

		void play();												// Joue la partie du début à la fin
};