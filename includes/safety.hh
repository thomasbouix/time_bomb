#pragma once
#include "card.hh"

class Safety : public Card {

	public :
		Safety();
		virtual std::string to_string() const;
};