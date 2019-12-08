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

	int safeties = 0;
	int defusers = 0;
	int bomb = 0;

	std::string res = "Game :\n";
	
	for (std::vector<Card*>::iterator it = full_deck.begin(); it != full_deck.end(); it++) {
		res = res + (*it)->to_string() + " / ";
		if (typeid(**it) == typeid(Safety)) safeties ++;
		else if (typeid(**it) == typeid(Defuser)) defusers++;
		else if(typeid(**it) == typeid(Bomb)) bomb++;
	}

	res = res.substr(0, res.size() - 2) + '\n';
	res = res + "Safeties = " + std::to_string(safeties) + "; Defusers = " + std::to_string(defusers) + "; Bomb = " + std::to_string(bomb);
	res += "\n==========\n";
	
	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); it++) {
		res = res + (*it)->to_string() + '\n';
	}

	res += "==========\n";
	return res;
}


// Distribution dans l'ordre de full_deck donc non-aléatoire --> A CORRIGER
void Game::deal() {

	// On vide le deck de chaque joueur
	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); it++) {
		(*it)->clear_deck();
	}

	int i_player = 0;	// Joueur à servir 

	// Distribution effective
	for (std::vector<Card*>::iterator it = full_deck.begin(); it != full_deck.end(); it++) {
		players[i_player]->add_card((*it));

		if (i_player == nb_players - 1) 
			i_player = 0;
		else 
			i_player++;
	}
}

void Game::draw(Player* a, Player* b, int card) {

	// Penser à delete la carte dans Game::full_deck après l'avoir retirer de Player::deck
	/*
	 * a->draw(b, card);
	 */
}