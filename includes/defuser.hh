#pragma once
#include "card.hh"

class Defuser : public Card {

	public : 
		Defuser();
		virtual std::string to_string() const;
};
