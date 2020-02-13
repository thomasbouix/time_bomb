#pragma once
#include "card.hh"

class Defuser : public Card {

	public : 
		Defuser();
		~Defuser();
		virtual std::string to_string() const;
};
