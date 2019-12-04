#pragma once
#include "card.hh"

class Bomb : public Card {

	public :
		Bomb();
		virtual std::string to_string() const;
};
