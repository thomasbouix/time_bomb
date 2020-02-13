#include "../../includes/game.hh"

Game::Game(int nb_players, int port) {

	this->chat = new Chatbox(port,nb_players);
	(*chat).print_clients();
	(*chat).broadcast_message("Let's get started now!\n"); // erreur ICI

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
	fill_players((*chat).get_name_players());
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

// instancie toutes les cartes du jeu
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

// instancie tous les joueurs du jeu
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

	// COMMUNICATION PROTOCOLE RESEAU
	// J joueur1 joueur2 joueur3 : message different pour chaque joueur
	std::string name;
	std::string message_;
	message_ = "J ";
	for (auto& p : players) {
		for (auto& p1 : players) {
			if (p != p1)
				message_ += p1->get_name() + " ";
		}
		name = (*p).get_name();
		Chatbox::send_message((*chat).get_port_client(name), (*chat).get_ip_client(name), message_);
		std::cout << message_ << std::endl;
		message_ = "J ";
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

// Distribue les cartes et actualise les variables de jeu
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

	// montre couleur à chaque joueur et communique
	for(auto& x : players) {

		std::string name = (*x).get_name();
		int port = (*chat).get_port_client(name);
		std::string ip = (*chat).get_ip_client(name);
		std::string color_ = (*x).get_color();

		// TO_STRING CONSOLE
		std::string message = name + ", your color is " + color_ + "\n";
		Chatbox::send_message(port, ip, message);

		// MESSAGES PROTOCOLE COMMUNICATION
		message = "";
		if (color_ == "blue") {
			message = "P 0";
			std::cout << message << std::endl;
		}
		else if (color_ == "red") {
			message = "P 1";
			std::cout << message << std::endl;
		}
		Chatbox::send_message(port, ip, message); 				// attribution du rôle P 
		std::cout << message << std::endl;
		Chatbox::send_message(port, ip, (*x).get_deck_str()); 	// etat du deck F S B S D (f = fill)
		std::cout << (*x).get_deck_str() << std::endl;
	}
}

void Game::play() {

	bool can_draw;

	deal();

	next_player = players[0];		// Joueur qui a la main
	previous_player = players[0];	// Joueur qui vient de jouer

	std::string line = "";

	// (*chat).broadcast_message(to_string());	// affiche la partie pour tous les joueurs

	// déroulement de la partie
	while (!bomb_found && (def_found < nb_defusers) && nb_round < 4) {

		std::cout << to_string();

		// Variables pour l'extraction des données du buffer réseau
		std::string target, drawer, action;
		int card;	// indice de la carte tirée

		// (*chat).broadcast_message("admin : " + next_player->get_name() + ", your turn to play\n");

		while (global_buffer.size() == 0);		// attend de recevoir un message 

		std::stringstream ss(global_buffer);	// permet d'utiliser global_buffer comme d'un stream
		std::string message;					// une ligne du global_buffer

		// tant qu'il y a une ligne à lire dans le global_buffer (messages réseaux des clients)
		while (getline(ss, message, '\n')) {

			// traitement du protocole réseau
			std::transform(message.begin(), message.end(), message.begin(), tolower);
			std::string::size_type pos = message.find("draw");

			if (pos != std::string::npos) {
				std::stringstream iss(message);					// utilisation du message comme d'un stream
				iss >> drawer >> action >> target >> card;  	// extraction data
				drawer = drawer.substr(0, drawer.length()-1);	// retire les deux points

				// déclaration d'un tirage : 
				if (action == "draw") {
					// le joueur qui tire n'avait pas la main
					if (drawer != next_player->get_name()) {
						can_draw = false;
						// (*chat).broadcast_message("admin :" + drawer + ", it is not your time to play!\n");
						global_buffer = "";	// sinon bug
					}
					// la target n'existe pas
					else if (!is_a_player(target)) {
						can_draw = false;
						// (*chat).broadcast_message("admin : this player does not exist\n");
						global_buffer = "";
					}
					// le joueur se tire lui-même
					else if (target == next_player->get_name()) {
						can_draw = false;
						// (*chat).broadcast_message("admin :" + drawer + ", you can not draw yourself!\n");
						global_buffer = "";
					}
					// le joueur tire sur son père
					else if (target == previous_player->get_name()) {
						can_draw = false;
						// (*chat).broadcast_message("admin :" + drawer + ", you can not draw your own father!\n");
						global_buffer = "";	// sinon bug
					}
					// tirage légal
					else if (drawer == next_player->get_name() && target != previous_player->get_name() 
						&& target != next_player->get_name()) {
						can_draw = true;
						break;
					}
				}
				// message normal - pas d'action
				else {	
					can_draw = false;
					global_buffer = "";
				}
			}
			else
				global_buffer = "";	// sinon bug
		}

		if(can_draw) {
			can_draw = false;
			global_buffer = "";

			// On tente un tirage
			if(play_draw(next_player, target, card)) {
				drew_cards_rd++;
				// (*chat).broadcast_message(to_string());	// affiche la partie pour tous les joueurs à chaque tirage 

				// MESSAGES PROTOCOLE RESEAU
				std::string message;
				message = "C " + std::to_string(drew_cards_rd);  			 // cartes tirées dans le round
				(*chat).broadcast_message(message);
				std::cout << message << std::endl;

				message = "D " + std::to_string(def_found);					 // defusers trouvé dans la partie
				(*chat).broadcast_message(message);
				std::cout << message << std::endl;

				message = "A " + target + " " + std::to_string(card) + " " + last_card_drew; // dernière cartes tirées A theo 2 S
				(*chat).broadcast_message(message);
				std::cout << message << std::endl;
			}
			else
				std::cout << "No cards to draw !\n";

			if (drew_cards_rd == nb_players) {
				std::cout << "END ROUND\n";
				drew_cards_rd = 0;
				nb_round++;
				deal();
				// TO_STRING CONSOLE
				(*chat).broadcast_message(to_string()); // montre la nouvelle distribution
				
				// MESSAGES PROTOCOLE RESEAU
				message = "R " + std::to_string(nb_round);  		// nombre de round joués
				(*chat).broadcast_message(message);
				std::cout << message << std::endl;
				message = "C " + std::to_string(drew_cards_rd);		// cartes tirées dans le round
				(*chat).broadcast_message(message);
				std::cout << message << std::endl;
			}
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

// utilisée par game::play_draw
bool Game::draw(Player* a, Player* b, int card) {

	// Pas de carte à piocher
	if (b->get_size_deck() == 0) {
		return false;
	}

	Card * removed_card = b->get_card(card);	// Pointeur sur la carte à supprimer

	if (typeid(*removed_card) == typeid(Safety)) {
		std::cout << "Safety found !\n";
		last_card_drew = 'S';	// protocole de communication
	}
	else if (typeid(*removed_card) == typeid(Defuser)) {
		std::cout << "Defuser found !\n";
		def_found++;
		last_card_drew = 'D'; 	// protocole de communication
	}
	else if (typeid(*removed_card) == typeid(Bomb)) {
		std::cout << "Bomb found !\n";
		bomb_found++;
		last_card_drew = 'B'; 	// protocole de communication
	}

	a->draw(b, card);			// Supprime le pointeur du player::deck

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
	previous_player = a;

	return true;
}

// utilisée dans game::play()
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

// non utilisée
bool Game::test_draw(int a, int b, int c) {

	// Empeche les seg fault
	int res_a = a % players.size();
	int res_b = b % players.size();

	return draw(players[res_a], players[res_b], c);
}

// non utilisée 
bool Game::draw(std::string message) {

	std::string sdrawer, starget, action;
	int card;

	std::stringstream iss(message);

	iss >> sdrawer >> action >> starget >> card;  // extraction data

	sdrawer = sdrawer.substr(0, sdrawer.length()-1);	// retire les deux points

	Player * pdrawer;
	Player * ptarget;

	// recherche du tireur
	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); it++) {
		if ((*it)->get_name() == sdrawer) {
			pdrawer = *it;
			break;
		}
	}

	// recherche de la cible
	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); it++) {
		if ((*it)->get_name() == starget) {
			ptarget = *it;
			break;
		}
	}

	return draw(pdrawer, ptarget ,card);
}

bool Game::is_a_player(std::string name) {

	for (auto& x : players) {
		if (x->get_name() == name)
			return true;
	}

	return false;
}
