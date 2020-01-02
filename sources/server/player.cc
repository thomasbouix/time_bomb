#include "../../includes/player.hh"

Player::~Player() {
	// std::cout << "Player deleted from memory\n";
}

Player::Player() {

	// on change la seed entre deux instanciations
	static int alea = 0;
	srand(time(NULL) + alea);
	alea++;

	// Couleur initialisée, puis modifiée si besoin avec Bot(int)
	color = rand() % 2;		

	int n = rand() % 5;

	switch (n) {
		case 0 : name = "Alfred";
			break;
		case 1 : name = "Benjamin";
			break;
		case 2 : name = "Charles";
			break;
		case 3 : name = "David";
			break;
		case 4 : name = "Edward";
			break;
		default :
			break;
	} 
}

Player::Player(int c, std::string n) : color(c), name(n) {}

std::string Player::get_name(void) const {
	return name;
}

std::string Player::to_string() {

	std::string str_color;

	if (color)
		str_color = "red";
	else 
		str_color = "blue";

	std::string res = this->get_name() + "(" + str_color + ") : ";

	// if (color) res = res + ", RED : \n";
	// else res = res + ", BLUE : \n"; 

	for (std::vector<Card*>::iterator it = deck.begin(); it != deck.end(); it++) {
		// res = res + (*it)->to_string() + " / ";
		res += "* / ";
	}
	res = res.substr(0, res.size() - 2);
	return res + '\n';
}

void Player::add_card(Card* card) {

	deck.push_back(card);
	// std::cout << card->to_string() << " card added\n" ;
}

void Player::remove_card(int card) {

	if (deck.size() == 0) {
		std::cout << "No card to remove\n";
		return;
	}

	int removed_card = card % deck.size();		// Elimine les indices trop grands

	// std::cout << deck[removed_card]->to_string() << " removed ! \n";
	
	deck.erase(deck.begin() + removed_card);
}

void Player::clear_deck() {
	deck.clear();
}

void Player::draw(Player* p, int card) {

	// std::cout << "Targeted draw !\n";

	(*p).remove_card(card);
}

Card* Player::get_card(int card) {

	int i_res = card % deck.size();

	return deck[i_res];
} 

int Player::get_size_deck() const  {
	return deck.size();
}