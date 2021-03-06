#pragma once
#include <typeinfo>
#include <sstream>
#include <string>

#include "chatbox.hh"

#include "player.hh"
#include "real.hh"
#include "weak.hh"
#include "strong.hh"

#include "card.hh"
#include "safety.hh"
#include "defuser.hh"
#include "bomb.hh"

class Game {

	private :

		Chatbox* chat;

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
		Player * previous_player;			// Joueur qui vient de tirer

	public :
		Game(int nb_players, int port);
		~Game();

		void fill_deck();											// Instancie toutes les cartes du jeu
		void fill_players(std::vector<std::string> real_players);	// Instancie tous les joueurs réels et complète avec des bots
		void deal();												// Distribue les cartes encore en jeu, actualise nb_round, drew_cards_rd

		// Les draw() renvoient true si elles réussissent le tirage
		bool draw(Player* a, Player* b, int card);					// pa pioche une carte chez pb, avec contrôle sur la sécurité
		bool test_draw(int a, int b, int c);						// draw avec des indices, utilise game::draw(Player*, Player*, int)
		bool play_draw(Player* nxt, std::string target, int card);	// fonction qu'utilise game::play()
		bool draw(std::string message);								// draw à partir du buffer venant du chat

		std::string to_string();

		void play();												// Joue la partie du début à la fin
		bool is_a_player(std::string name);							// vrai si le nom fourni est celui d'un joueur

		char last_card_drew;										// S D B
};
