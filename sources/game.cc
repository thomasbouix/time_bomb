#include "../includes/game.hh"
#include "../includes/safety.hh"
#include "../includes/defuser.hh"
#include "../includes/bomb.hh"

Game::Game(int nb_players) {

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
				std::cout << "error fill_deck";
				break;
		}
	}
}

std::string Game::to_string() {

	std::string res = "Game :\n";

	for (std::vector<Card*>::iterator it = full_deck.begin(); it != full_deck.end(); it++) {
		res = res + (*it)->to_string() + " / ";
	}
	res = res.substr(0, res.size() - 2);
	return res + '\n';
}