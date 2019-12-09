#include "../includes/game.hh"

#include "../includes/safety.hh"
#include "../includes/defuser.hh"
#include "../includes/bomb.hh"

#include "../includes/player.hh"
#include "../includes/real.hh"
#include "../includes/weak.hh"
#include "../includes/strong.hh"

Game::Game(int nb_players, std::vector<std::string> real_players) {

	this->nb_players = nb_players;
	this->nb_round = 0;
	this->drew_cards_rd = 0;
	this->def_found = 0;
	this->bomb_found = 0;

	switch (nb_players) {
		case 4 : // Une carte non distribuée
			nb_blue = 3; nb_red = 2;
			nb_safeties = 15; nb_defusers = 4;
			break;
		case 5 :
			nb_blue = 3; nb_red = 2;
			nb_safeties = 19; nb_defusers = 5;
			break;
		case 6 :
			nb_blue = 4; nb_red = 2;
			nb_safeties = 23; nb_defusers = 6;
			break;
		case 7 : // Une carte non distribuée
			nb_blue = 5; nb_red = 3;
			nb_safeties = 27; nb_defusers = 7;
			break;
		case 8 :
			nb_blue = 5; nb_red = 3;
			nb_safeties = 31; nb_defusers = 8;
			break;
		default :
			std::cout << "Number of players invalid\n";
			return;
	}

	fill_deck();
	fill_players(real_players);
}

Game::~Game() {

	// suppression des cartes
	for (std::vector<Card*>::iterator it = full_deck.begin(); it != full_deck.end(); it++) {
		delete *it;
	}

	// Suppression des joueurs
	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); it++) {
		delete *it;
	}
}

void Game::fill_deck() {

	srand(time(NULL));
	int nb_card = nb_safeties + nb_defusers + 1;
	int safeties_done = 0;
	int defusers_done = 0;
	int bomb_done = 0;
	int cards_done = 0;

	while (cards_done != nb_card) {

		int card = rand() % 3;
		switch (card) {
			case 0 :
				if (safeties_done < nb_safeties) {
					full_deck.push_back(new Safety());
					safeties_done++; cards_done++;
				}
				break;
			case 1 :
				if (defusers_done < nb_defusers) {
					full_deck.push_back(new Defuser());
					defusers_done++; cards_done++;
				}
				break;
			case 2 : 
				if (bomb_done < 1) {
					full_deck.push_back(new Bomb());
					bomb_done++; cards_done++;
				}
				break;
			default :
				return;
		}
	}
}

void Game::fill_players(std::vector<std::string> real_players) {
	srand(time(NULL));

	int players_done = 0;
	int red_done = 0;
	int blue_done = 0;

	// instanciation des joueurs réels d'abord
	while ((size_t) players_done != real_players.size()) {
		int color = rand() % 2;
		switch (color) {
			case BLUE :
				if (blue_done < nb_blue) {
					players.push_back(new Real(BLUE, real_players[players_done]));
					// std::cout << "Blue added : " << real_players[players_done] << '\n';
					blue_done++; players_done++;
				} 
				break;
			case RED :
				if (red_done < nb_red) {
					players.push_back(new Real(RED, real_players[players_done]));
					// std::cout << "Red added : " << real_players[players_done] << '\n';
					red_done++; players_done++;
				}
				break;
			default :
				return;
		}
	}

	// Complétion avec des Bot
	while (players_done != nb_players) {
		int color = rand() % 2;
		switch (color) {
			case BLUE :
				if (blue_done < nb_blue) {
					players.push_back(new Weak(BLUE));
					// std::cout << "Blue Bot added" << '\n';
					blue_done++; players_done++;
				} 
				break;
			case RED :
				if (red_done < nb_red) {
					players.push_back(new Weak(RED));
					// std::cout << "Red Bot added" << '\n';
					red_done++; players_done++;
				}
				break;
			default :
				return;
		}
	} 
}

std::string Game::to_string() {

	std::string res = "=============\n";
	
	// Affiche full_deck
	/*
	int safeties = 0;
	int defusers = 0;
	int bomb = 0;
	for (std::vector<Card*>::iterator it = full_deck.begin(); it != full_deck.end(); it++) {
		res = res + (*it)->to_string() + " / ";
		if (typeid(**it) == typeid(Safety)) safeties ++;
		else if (typeid(**it) == typeid(Defuser)) defusers++;
		else if(typeid(**it) == typeid(Bomb)) bomb++;
	}
	*/

	res = res.substr(0, res.size() - 2);
	// res += "Safeties = " + std::to_string(safeties);
	// res += "; Defusers = " + std::to_string(defusers);
	// res += "; Bomb = " + std::to_string(bomb);
	// res += "\n===";
	res += "\nRound n° : " + std::to_string(nb_round);
	res += "\nCards drew in this round : " + std::to_string(drew_cards_rd);
	res += "\nDefusers found : " + std::to_string(def_found); 
	res += "\n===\n";
	
	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); it++) {
		res = res + (*it)->to_string() + '\n';
	}
	res = res.substr(0, res.size() - 1);
	res += "=============\n";
	return res;
}

void Game::deal() {

	// ======== On vide le deck de chaque joueur ========
	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); it++) {
		(*it)->clear_deck();
	}

	// ======= Distribution effective (aléatoire) =======
	srand(time(NULL));
	// Tableau représentant full_deck : 0 <=> carte non distribuée
	int * deck_aux = new int[full_deck.size()]();
	// Nombre de cartes restantes à distribuer
	int nb_to_deal = full_deck.size();
	// Joueur à servir 
	int i_player = 0;

	while (nb_to_deal != 0) {
		
		int card_to_deal = rand() % nb_to_deal; 	// selectionne une carte à distribuer parmis les 0
		int i_deck = 0; 							// parcours le deck jusqu'à atteindre la carte à distribuer
		int i_card_to_deal = 0; 					// parcours les cartes restantes (=>0)
	
		// On se positionne sur le premier 0
		while(deck_aux[i_deck] == 1) 
			i_deck++;

		// Trouve l'indice de la carte à distribuer
		while (i_card_to_deal != card_to_deal) {
			i_deck++;
			if (deck_aux[i_deck] == 0)
				i_card_to_deal++;
		}

		players[i_player]->add_card(full_deck[i_deck]); // Distribue la carte

		if (i_player == nb_players - 1) 
			i_player = 0;
		else 
			i_player++;
		
		deck_aux[i_deck] = 1; // Met à jour le tableau auxilliaire
		nb_to_deal--;
	}
	delete[] deck_aux;
}

bool Game::draw(Player* a, Player* b, int card) {

	// Pas de carte à piocher
	if (b->get_size_deck() == 0) {
		return false;
	}

	Card * removed_card = b->get_card(card);	// Pointeur sur la carte à supprimer

	if (typeid(*removed_card) == typeid(Safety)) {
		std::cout << "Safety found !\n";
	}
	else if (typeid(*removed_card) == typeid(Defuser)) {
		std::cout << "Defuser found !\n";
		def_found++;
	}
	else if (typeid(*removed_card) == typeid(Bomb)) {
		std::cout << "Bomb found !\n";
		bomb_found++;
	}

	a->draw(b, card);	// Supprime le pointeur du player::deck

	 // Supprime le pointeur du game::full_deck
	for (std::vector<Card*>::iterator it = full_deck.begin(); it != full_deck.end(); it++) {
		if (*it == removed_card) {
	 		full_deck.erase(it);
	 		break;
	 	}
	}

	// Supprime l'objet et donc aussi le pointeur du game::full_deck 
	delete removed_card;

	next_player = b;

	return true;
}

void Game::play() {

	deal();

	next_player = players[0];

	std::string line = "";

	while (!bomb_found && (def_found < nb_defusers) && nb_round < 4) {

		std::cout << to_string();

		std::string target;
		int c;

		std::cout << next_player->get_name() << ", your turn to play :\n";

		std::cin >> target;
		std::cin >> c;

		if (target == next_player->get_name()) {
			std::cout << "You can not draw your own card\n";
			continue;
		}

		if(play_draw(next_player, target, c))
			drew_cards_rd++;
		else 
			std::cout << "No cards to draw !\n";

		if (drew_cards_rd == nb_players) {
			std::cout << "END ROUND\n";
			drew_cards_rd = 0;
			nb_round++;
			deal();
		}
	}

	// ===== END GAME ====
	if (bomb_found)
		std::cout << "BOOM ! So many smoke !\n";
	else if (def_found == nb_defusers)
		std::cout << "Bomb defused !\n";
	else 
		std::cout << "No more rounds !\n";

	std::cout << "END GAME\n";
}

bool Game::play_draw(Player* nxt, std::string target, int c) {

	Player* t = NULL;

	// Cherche le player* cible en fonciton de son nom
	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); it++) {
		if ((*it)->get_name() == target) {
			t = *it;
			break;
		}
	}

	if (t == NULL) {
		std::cout << "Incorrect player name\n";
		return false;
	}

	return draw(nxt, t, c);
}

bool Game::test_draw(int a, int b, int c) {

	// Empeche les seg fault
	int res_a = a % players.size();
	int res_b = b % players.size();

	return draw(players[res_a], players[res_b], c);
}
